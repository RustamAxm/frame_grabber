import ctypes
import sys
import time

import numpy as np
import queue
import threading
import logging

from ctypes.wintypes import HANDLE
from helpers.loggin_helper import set_logging
from modules.struct_header import TapConfigPredefined, VCECLB_FrameInfoEx, \
    VCECLB_RawPixelInfoEx, VCECLB_CameraDataEx

logger = logging.getLogger('modules')

VCECLB_Err_Success = 0

VCECLB_EX_FMT_8BIT = 0
VCECLB_EX_FMT_16BIT = 1
VCECLB_EX_FMT_16BIT_NORMALIZE = 3


class FrameGrabber:
    def __init__(self, Width=1024, Height=1152, BitDepth=10, Packed=1):
        set_logging(logger, verbose='')
        self.m_RawPixelInfoEx = VCECLB_RawPixelInfoEx()
        self.Width = Width
        self.Height = Height
        self.Packed = Packed
        self.BitDepth = BitDepth
        self._set_pixel_info()
        self.dll = ctypes.WinDLL(r'modules/imperx_dll/Release/VCECLB.dll')
        self.queue_ = queue.Queue(maxsize=5)
        self.dll.VCECLB_Init.argtypes = None
        self.dll.VCECLB_Init.restype = HANDLE
        self.m_DeviceID = self.dll.VCECLB_Init()

        if self.m_DeviceID:
            logger.info(f'device ID = {self.m_DeviceID}')
        else:
            logger.error("No FrameLink Express card detected!")
            self.close_device()
            sys.exit(1)

        self.m_nPort = ctypes.c_char(0)
        self.dll.VCECLB_GetDMAAccessEx.argtypes = ctypes.c_void_p, ctypes.c_char
        self.dll.VCECLB_GetDMAAccessEx.restypes = ctypes.c_uint32
        err = self.dll.VCECLB_GetDMAAccessEx(self.m_DeviceID, self.m_nPort)
        if err == VCECLB_Err_Success:
            logger.info('GetDMAAccessEx OK')
        else:
            logger.error("Bad Port or port busy")
            self.close_device()
            sys.exit(1)

        self._prep_settings()

    def grab_thread(self):
        self.thread_bool = True
        self.x_thread = threading.Thread(target=self._start_grab)
        self.x_thread.start()

    def get_image(self):
        buffer = self.queue_.get()
        self.queue_.task_done()

        self.img = np.frombuffer(self.unpack_image(buffer), dtype=np.uint16).reshape(self.Height, self.Width)

        img_cut_up = self.img[0:int(self.Height / 2), 0:self.Width]
        img_cut_down = self.img[int(self.Height / 2):self.Height, 0:self.Width]
        self.img = np.row_stack((img_cut_up[:, :], img_cut_down[::-1, :]))
        return self.img

    def close_device(self):
        self.dll.VCECLB_StopGrabEx.argtypes = [ctypes.c_void_p, ctypes.c_char]
        self.dll.VCECLB_StopGrabEx.restype = ctypes.c_uint32
        self.dll.VCECLB_StopGrabEx(self.m_DeviceID, self.m_nPort)

        self.dll.VCECLB_ReleaseDMAAccessEx.argtypes = [ctypes.c_void_p, ctypes.c_char]
        self.dll.VCECLB_ReleaseDMAAccessEx.restype = ctypes.c_uint32
        self.dll.VCECLB_ReleaseDMAAccessEx(self.m_DeviceID, self.m_nPort)

        self.thread_bool = False
        self.x_thread.join()

        self.dll.VCECLB_Done.argtypes = [ctypes.c_void_p]
        self.dll.VCECLB_Done.restype = ctypes.c_uint32
        self.dll.VCECLB_Done(self.m_DeviceID)

    def _q_clear(self):
        with self.queue_.mutex:
            self.queue_.queue.clear()

    def _start_grab(self):
        @ctypes.CFUNCTYPE(None, ctypes.c_void_p, VCECLB_FrameInfoEx)
        def grabThread(a, pFrameInfo):
            logger.debug(f' pFrameInfo.bufferSize = {pFrameInfo.bufferSize}')
            buffer = (ctypes.c_char * pFrameInfo.bufferSize)()
            ctypes.memmove(buffer,  pFrameInfo.lpRawBuffer,  pFrameInfo.bufferSize)
            self.queue_.put(buffer, block=False, timeout=0.01)

        self.dll.VCECLB_StartGrabEx.argtypes = [ctypes.c_void_p, ctypes.c_char,
                                                ctypes.c_uint32, ctypes.c_void_p,
                                                ctypes.c_void_p]
        self.dll.VCECLB_StartGrabEx.restypes = ctypes.c_uint32
        err = self.dll.VCECLB_StartGrabEx(self.m_DeviceID,
                                          self.m_nPort,
                                          0,
                                          grabThread, None)
        logger.debug(f'VCECLB_StartGrabEx err = {err}')

        if err != VCECLB_Err_Success:
            logger.error('VCECLB_StartGrabEx error')
            self.close_device()
            sys.exit(1)

        while self.thread_bool:
            time.sleep(0.05)
            self._q_clear()

    def unpack_image(self, buffer_in):
        pOutputBitDepth = ctypes.c_uint32(self.BitDepth)
        pStrideSize = ctypes.c_uint32(self.Width * 2)
        logger.debug(f'buffer_in len = {len(buffer_in)}')

        self.dll.VCECLB_UnpackRawPixelsEx.argtypes = [ctypes.POINTER(VCECLB_RawPixelInfoEx),
                                                      ctypes.c_void_p,
                                                      ctypes.c_void_p,
                                                      ctypes.c_void_p,
                                                      ctypes.c_uint8,
                                                      ctypes.POINTER(ctypes.c_uint32)]
        self.dll.VCECLB_UnpackRawPixelsEx.restype = ctypes.c_uint32

        tmp_buffer = (ctypes.c_char * int(self.Height * self.Width * 2))()
        err = self.dll.VCECLB_UnpackRawPixelsEx(ctypes.byref(self.m_RawPixelInfoEx),
                                                ctypes.byref(buffer_in),
                                                ctypes.byref(tmp_buffer),
                                                ctypes.byref(pStrideSize),
                                                VCECLB_EX_FMT_16BIT,
                                                ctypes.byref(pOutputBitDepth))

        logger.debug(f'tmp_buffer len = {len(tmp_buffer)}')
        logger.debug(f'VCECLB_UnpackRawPixelsEx err = {err}')
        if err != VCECLB_Err_Success:
            logger.error('UnpackRawPixelsEx error')

        return tmp_buffer

    def _prep_settings(self):
        self.dll.VCECLB_GetPredefinedTapConfig(TapConfigPredefined.VCECLB_TapConfig_8TapInterLR,
                                                ctypes.byref(self.m_RawPixelInfoEx.cameraData.TapConfig))
        
        self.dll.VCECLB_PrepareEx.argtypes = [ctypes.c_void_p, ctypes.c_char, ctypes.POINTER(VCECLB_CameraDataEx)]
        self.dll.VCECLB_PrepareEx.restypes = ctypes.c_uint32
        err = self.dll.VCECLB_PrepareEx(self.m_DeviceID,
                                        self.m_nPort,
                                        ctypes.byref(self.m_RawPixelInfoEx.cameraData))
        logger.debug(f'VCECLB_PrepareEx err = {err}')

        if err != VCECLB_Err_Success:
            logger.error('VCECLB_PrepareEx error')
            self.close_device()
            sys.exit(1)

    def _set_pixel_info(self):
        self.m_RawPixelInfoEx.cameraData.WidthPreValid = 0
        self.m_RawPixelInfoEx.cameraData.WidthPostValid = 0
        self.m_RawPixelInfoEx.cameraData.Width = self.Width
        self.m_RawPixelInfoEx.cameraData.HeightPreValid = 0
        self.m_RawPixelInfoEx.cameraData.HeightPostValid = 0
        self.m_RawPixelInfoEx.cameraData.Height = self.Height

        self.m_RawPixelInfoEx.cameraData.BitDepth = self.BitDepth
        self.m_RawPixelInfoEx.cameraData.Packed = self.Packed

        self.m_RawPixelInfoEx.cameraData.IgnoreDVAL = 0
        self.m_RawPixelInfoEx.cameraData.InvertDVAL = 0
        self.m_RawPixelInfoEx.cameraData.InvertFVAL = 0
        self.m_RawPixelInfoEx.cameraData.InvertLVAL = 0

        self.m_RawPixelInfoEx.BayerPattern = 0
        self.m_RawPixelInfoEx.BayerStart = 0
        self.m_RawPixelInfoEx.BlueGain = 0
        self.m_RawPixelInfoEx.BlueOffset = 0
        self.m_RawPixelInfoEx.GreenGain = 0
        self.m_RawPixelInfoEx.GreenOffset = 0
        self.m_RawPixelInfoEx.RedGain = 0
        self.m_RawPixelInfoEx.RedOffset = 0

