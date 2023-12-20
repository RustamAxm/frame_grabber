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
from multiprocessing import Process

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
    for i in range(0, len(ibuffer), BLOCK_SIZE):
        obuffer[k] = ((ibuffer[i + 1] & 0x03) << 8) | ((ibuffer[i + 0] >> 0) & 0xFF)
        k += 1
        obuffer[k] = ((ibuffer[i + 2] & 0x0F) << 6) | ((ibuffer[i + 1] >> 2) & 0x3F)
        k += 1
        obuffer[k] = ((ibuffer[i + 3] & 0x3F) << 4) | ((ibuffer[i + 2] >> 4) & 0x0F)
        k += 1
        obuffer[k] = ((ibuffer[i + 4] & 0xFF) << 2) | ((ibuffer[i + 3] >> 6) & 0x03)
        k += 1

        obuffer[k] = ((ibuffer[i + 6] & 0x03) << 8) | ((ibuffer[i + 5] >> 0) & 0xFF)
        k += 1
        obuffer[k] = ((ibuffer[i + 7] & 0x0F) << 6) | ((ibuffer[i + 6] >> 2) & 0x3F)
        k += 1
        obuffer[k] = ((ibuffer[i + 8] & 0x3F) << 4) | ((ibuffer[i + 7] >> 4) & 0x0F)
        k += 1
        obuffer[k] = ((ibuffer[i + 9] & 0xFF) << 2) | ((ibuffer[i + 8] >> 6) & 0x03)
        k += 1

        obuffer[k] = ((ibuffer[i + 11] & 0x03) << 8) | ((ibuffer[i + 10] >> 0) & 0xFF)
        k += 1
        obuffer[k] = ((ibuffer[i + 12] & 0x0F) << 6) | ((ibuffer[i + 11] >> 2) & 0x3F)
        k += 1
        obuffer[k] = ((ibuffer[i + 13] & 0x3F) << 4) | ((ibuffer[i + 12] >> 4) & 0x0F)
        k += 1
        obuffer[k] = ((ibuffer[i + 14] & 0xFF) << 2) | ((ibuffer[i + 13] >> 6) & 0x03)
        k += 1

        obuffer[k] = ((ibuffer[i + 16] & 0x03) << 8) | ((ibuffer[i + 15] >> 0) & 0xFF)
        k += 1
        obuffer[k] = ((ibuffer[i + 17] & 0x0F) << 6) | ((ibuffer[i + 16] >> 2) & 0x3F)
        k += 1
        obuffer[k] = ((ibuffer[i + 18] & 0x3F) << 4) | ((ibuffer[i + 17] >> 4) & 0x0F)
        k += 1
        obuffer[k] = ((ibuffer[i + 19] & 0xFF) << 2) | ((ibuffer[i + 18] >> 6) & 0x03)
        k += 1

        obuffer[k] = ((ibuffer[i + 21] & 0x03) << 8) | ((ibuffer[i + 20] >> 0) & 0xFF)
        k += 1
        obuffer[k] = ((ibuffer[i + 22] & 0x0F) << 6) | ((ibuffer[i + 21] >> 2) & 0x3F)
        k += 1
        obuffer[k] = ((ibuffer[i + 23] & 0x3F) << 4) | ((ibuffer[i + 22] >> 4) & 0x0F)
        k += 1
        obuffer[k] = ((ibuffer[i + 24] & 0xFF) << 2) | ((ibuffer[i + 23] >> 6) & 0x03)
        k += 1

        obuffer[k] = ((ibuffer[i + 26] & 0x03) << 8) | ((ibuffer[i + 25] >> 0) & 0xFF)
        k += 1
        obuffer[k] = ((ibuffer[i + 27] & 0x0F) << 6) | ((ibuffer[i + 26] >> 2) & 0x3F)
        k += 1
        obuffer[k] = ((ibuffer[i + 28] & 0x3F) << 4) | ((ibuffer[i + 27] >> 4) & 0x0F)
        k += 1
        obuffer[k] = ((ibuffer[i + 29] & 0xFF) << 2) | ((ibuffer[i + 28] >> 6) & 0x03)
        k += 1

        obuffer[k] = ((ibuffer[i + 31] & 0x03) << 8) | ((ibuffer[i + 30] >> 0) & 0xFF)
        k += 1
        obuffer[k] = ((ibuffer[i + 32] & 0x0F) << 6) | ((ibuffer[i + 31] >> 2) & 0x3F)
        k += 1
        obuffer[k] = ((ibuffer[i + 33] & 0x3F) << 4) | ((ibuffer[i + 32] >> 4) & 0x0F)
        k += 1
        obuffer[k] = ((ibuffer[i + 34] & 0xFF) << 2) | ((ibuffer[i + 33] >> 6) & 0x03)
        k += 1

        obuffer[k] = ((ibuffer[i + 36] & 0x03) << 8) | ((ibuffer[i + 35] >> 0) & 0xFF)
        k += 1
        obuffer[k] = ((ibuffer[i + 37] & 0x0F) << 6) | ((ibuffer[i + 36] >> 2) & 0x3F)
        k += 1
        obuffer[k] = ((ibuffer[i + 38] & 0x3F) << 4) | ((ibuffer[i + 37] >> 4) & 0x0F)
        k += 1
        obuffer[k] = ((ibuffer[i + 39] & 0xFF) << 2) | ((ibuffer[i + 38] >> 6) & 0x03)
        k += 1

    obuffer.byteswap(inplace=True)

    return obuffer


def convert_image(filename, config):
    in_buffer = read_raw_to_buffer(filename)
    unpacked_buf = unpack_raw(in_buffer, config)
    logger.info(f'in buffer len = {len(in_buffer)}, unpacked buffer len = {len(unpacked_buf)}')
    save_unpacked(config['out_dir'] + os.sep + filename[:-4] + '_unpacked.raw', unpacked_buf)


def use_without_dll(config, files):
    for filename in files:
        Process(target=convert_image, args=(filename, config)).start()


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
