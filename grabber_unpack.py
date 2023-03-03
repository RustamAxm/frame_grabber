"""
Works only on Windows with an inserted card frame grabber
"""

import ctypes
import sys
import logging
import glob
import os
import errno

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
    if not os.path.exists(os.path.dirname(name)):
        try:
            os.makedirs(os.path.dirname(name))
        except OSError as exc:  # Guard against race condition
            if exc.errno != errno.EEXIST:
                raise

    with open(name, 'wb') as file:
        file.write(buffer)
    logger.info(f'raw data saved {name}')


if __name__ == '__main__':
    try:
        source_dir = sys.argv[1]
    except IndexError:
        source_dir = r'raw_data'

    try:
        out_dir = sys.argv[2]
    except IndexError:
        out_dir = 'unpacked'

    dir_ = 'raw_data'
    files = []
    for file in glob.glob(f'{source_dir}/**/*.raw', recursive=True):
        if file:
            files.append(file)

    grab = FrameGrabber(Width=2048, Height=1152, BitDepth=10, Packed=1)

    for filename in files:
        in_buffer = read_raw_to_buffer(filename)
        unpacked_buf = grab.unpack_image(in_buffer)
        logger.info(f'in buffer len = {len(in_buffer)}, unpacked buffer len = {len(unpacked_buf)}')
        save_unpacked(out_dir + '/' + filename[:-4] + '_unpacked.raw', unpacked_buf)


