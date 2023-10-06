"""
Works only on Windows with an inserted card frame grabber
"""

import ctypes
import sys
import logging
import glob
import os
import errno
import yaml

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
        source_config = sys.argv[1]
    except IndexError:
        source_config = r'config.yaml'

    with open(source_config, 'r') as yamlfile:
        config = yaml.safe_load(yamlfile)

    files = []
    for file in glob.glob(f'{config["in_dir"]}/**/*.raw', recursive=True):
        if file:
            files.append(file)

    grab = FrameGrabber(Width=config["Width"],
                        Height=config["Height"],
                        BitDepth=config["BitDepth"],
                        Packed=config["Packed"])

    for filename in files:
        in_buffer = read_raw_to_buffer(filename)
        unpacked_buf = grab.unpack_image(in_buffer)
        logger.info(f'in buffer len = {len(in_buffer)}, unpacked buffer len = {len(unpacked_buf)}')
        save_unpacked(config['out_dir'] + os.sep + filename[:-4] + '_unpacked.raw', unpacked_buf)
