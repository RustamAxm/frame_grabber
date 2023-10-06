import sys
import yaml
from matplotlib import pyplot as plt
from modules.grabber import FrameGrabber


if __name__ == '__main__':
    name = 'debug camera link raw data'

    try:
        source_config = sys.argv[1]
    except IndexError:
        source_config = r'config.yaml'

    with open(source_config, 'r') as yamlfile:
        config = yaml.safe_load(yamlfile)

    grab = FrameGrabber(Width=config["Width"],
                        Height=config["Height"],
                        BitDepth=config["BitDepth"],
                        Packed=config["Packed"])
    grab.grab_thread()

    img = grab.get_image()

    grab.close_device()

    plt.figure()
    plt.imshow(img, cmap='gray')
    plt.show()
