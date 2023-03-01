import ctypes
from ctypes import wintypes


class VCECLB_TapConfig(ctypes.Structure):
    _fields_ = [('channels', ctypes.c_ubyte),
                ('channelOrder', ctypes.c_ubyte),
                ('channelOutput', ctypes.c_ubyte),
                ('channelDirection', ctypes.c_ubyte * 2),
                ('taps', ctypes.c_ubyte),
                ('tapOutput', ctypes.c_ubyte),
                ('tapDirection', ctypes.c_ubyte * 4)]


class VCECLB_CameraDataEx(ctypes.Structure):
    _fields_ = [('WidthPreValid', ctypes.c_ulong),
                ('Width', ctypes.c_ulong),
                ('WidthPostValid', ctypes.c_ulong),
                ('HeightPreValid', ctypes.c_ulong),
                ('Height', ctypes.c_ulong),
                ('HeightPostValid', ctypes.c_ulong),
                ('BitDepth', ctypes.c_ulong),
                ('Packed', ctypes.c_ulong),
                ('TapConfig', VCECLB_TapConfig),
                ('SwapTaps', ctypes.c_ulong),
                ('IgnoreDVAL', ctypes.c_ulong),
                ('InvertDVAL', ctypes.c_ulong),
                ('InvertLVAL', ctypes.c_ulong),
                ('InvertFVAL', ctypes.c_ulong),
                ('LineScan', ctypes.c_ulong)]


class VCECLB_RawPixelInfoEx(ctypes.Structure):
    _fields_ = [('_unused0', ctypes.c_void_p),
                ('cameraData', VCECLB_CameraDataEx),
                ('BayerPattern', ctypes.c_ubyte),
                ('BayerStart', ctypes.c_ubyte),
                ('RedOffset', ctypes.c_byte),
                ('GreenOffset', ctypes.c_byte),
                ('BlueOffset', ctypes.c_byte),
                ('RedGain', ctypes.c_double),
                ('GreenGain', ctypes.c_double),
                ('BlueGain', ctypes.c_double),
                ('LookupTableLevels', ctypes.c_int),
                ('LookupTableValues', ctypes.c_int)]


class VCECLB_FrameInfoEx(ctypes.Structure):
    _fields_ = [('number', ctypes.c_uint32),
                ('timestamp', ctypes.c_uint32),
                ('lpRawBuffer', ctypes.c_void_p),
                ('bufferSize', ctypes.c_uint32),
                ('dma_status', ctypes.c_uint32)]


class SYSTEMTIME(ctypes.Structure):
    _fields_ = [('wYear', ctypes.wintypes.WORD),
                ('wMonth', ctypes.wintypes.WORD),
                ('wDayOfWeek', ctypes.wintypes.WORD),
                ('wDay', ctypes.wintypes.WORD),
                ('wHour', ctypes.wintypes.WORD),
                ('wMinute', ctypes.wintypes.WORD),
                ('wSecond', ctypes.wintypes.WORD),
                ('wMilliseconds', ctypes.wintypes.WORD)]


class TapConfigPredefined:
    (VCECLB_TapConfig_Custom,
     VCECLB_TapConfig_1TapLR,
     VCECLB_TapConfig_1TapRL,
     VCECLB_TapConfig_2TapInterLR,
     VCECLB_TapConfig_2TapInterRL,
     VCECLB_TapConfig_2TapSepLR,
     VCECLB_TapConfig_2TapSepRL,
     VCECLB_TapConfig_2TapSepCov,
     VCECLB_TapConfig_2TapSepDiv,
     VCECLB_TapConfig_3TapSepLR,
     VCECLB_TapConfig_4TapSepLR,
     VCECLB_TapConfig_4TapSepRL,
     VCECLB_TapConfig_4Tap2SegLR,
     VCECLB_TapConfig_4Tap2SegConv,
     VCECLB_TapConfig_4TapQuadConv,
     VCECLB_TapConfig_4TapInterLR,
     VCECLB_TapConfig_4TapInterRL,
     VCECLB_TapConfig_8TapInterLR,
     VCECLB_TapConfig_10TapInterLR) = map(ctypes.c_uint, range(19))

