from matplotlib import pyplot as plt
from modules.grabber import FrameGrabber


if __name__ == '__main__':
    name = 'debug camera link raw data'

    grab = FrameGrabber()
    grab.grab_thread()

    img = grab.get_image()

    grab.close_device()

    plt.figure()
    plt.imshow(img, cmap='gray')
    plt.show()
