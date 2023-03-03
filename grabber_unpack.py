"""
Works only on Windows with an inserted card frame grabber
"""

import ctypes
import sys
import logging

from modules.grabber import FrameGrabber
from helpers.loggin_helper import set_logging

logger = logging.getLogger('Unpack RAW')
set_logging(logger)


def read_raw_to_buffer(name):
    with open(name, 'rb') as file:
        data = file.read()

    buffer = (ctypes.c_char * len(data))()
    ctypes.memmove(buffer, data, len(data))
    return buffer


def save_unpacked(name, buffer):
    with open(name, 'wb') as file:
        file.write(buffer)
    logger.info(f'raw data saved {name}')


if __name__ == '__main__':
    try:
        name = sys.argv[1]
    except IndexError:
        name = r'raw_data/Азимут/Без дополнительного фильтра/Поле приемного СЛК НС2НС10.raw'

    try:
        out_name = sys.argv[2]
    except IndexError:
        out_name = name[:-4] + '_unpacked.raw'

    in_buffer = read_raw_to_buffer(name)
    grab = FrameGrabber(Width=2048, Height=1152, BitDepth=10, Packed=1)
    unpacked_buf = grab.unpack_image(in_buffer)
    logger.info(f'in buffer len = {len(in_buffer)}, unpacked buffer len = {len(unpacked_buf)}')
    save_unpacked(out_name, unpacked_buf)
