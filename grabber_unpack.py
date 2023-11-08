"""
Works only on Windows with an inserted card frame grabber
"""

import ctypes
import sys
import logging
import glob
import os
import errno

import numpy as np
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


def use_grab_card(config, files):
    grab = FrameGrabber(Width=config["Width"],
                        Height=config["Height"],
                        BitDepth=config["BitDepth"],
                        Packed=config["Packed"])

    for filename in files:
        in_buffer = read_raw_to_buffer(filename)
        unpacked_buf = grab.unpack_image(in_buffer)
        logger.info(f'in buffer len = {len(in_buffer)}, unpacked buffer len = {len(unpacked_buf)}')
        save_unpacked(config['out_dir'] + os.sep + filename[:-4] + '_unpacked.raw', unpacked_buf)


def unpack_raw(ibuffer, config):
    BLOCK_SIZE = 40
    k = 0
    ibuffer = np.frombuffer(ibuffer, dtype=np.uint8)
    obuffer = np.zeros(int(config["Height"] * config["Width"] * 2), dtype=np.uint16)
    for i in range(0, len(ibuffer) - BLOCK_SIZE, BLOCK_SIZE):
        for j in range(0, BLOCK_SIZE, 4):
            obuffer[k] = ((ibuffer[i + j + 1] & 0x03) << 8) | ((ibuffer[i + j + 0] >> 0) & 0xFF)
            k += 1
            obuffer[k] = ((ibuffer[i + j + 2] & 0x0F) << 6) | ((ibuffer[i + j + 1] >> 2) & 0x3F)
            k += 1
            obuffer[k] = ((ibuffer[i + j + 3] & 0x3F) << 4) | ((ibuffer[i + j + 2] >> 4) & 0x0F)
            k += 1
            obuffer[k] = ((ibuffer[i + j + 4] & 0xFF) << 2) | ((ibuffer[i + j + 3] >> 6) & 0x03)
            k += 1

    obuffer.byteswap(inplace=True)

    return obuffer


def use_without_dll(config, files):
    for filename in files:
        in_buffer = read_raw_to_buffer(filename)
        unpacked_buf = unpack_raw(in_buffer, config)
        logger.info(f'in buffer len = {len(in_buffer)}, unpacked buffer len = {len(unpacked_buf)}')
        save_unpacked(config['out_dir'] + os.sep + filename[:-4] + '_unpacked.raw', unpacked_buf)


def main():
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

    if config['without_lib']:
        use_without_dll(config, files)
    else:
        use_grab_card(config, files)


if __name__ == '__main__':
    main()
