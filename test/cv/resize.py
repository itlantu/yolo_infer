import cv2
import numpy as np
from matplotlib import pyplot as plt

def resize(image: np.ndarray, size: tuple[int, int]) -> np.ndarray:
    """ 等比缩放并且填充图像, 函数将尝试最大程度等比缩放原始图像, 并将缩放后的图像填充到指定尺寸
    
    :param image: 输入图像
    :param size: 输出图像的尺寸, 格式为(height, width)
    :return: 等比缩放并且填充后的图像
    """
    result = np.zeros((size[1], size[0], image.shape[2]), dtype=np.uint8)

    ah = image.shape[0] / size[0]
    aw = image.shape[1] / size[1]

    if ah == 1 and aw == 1:
        return image
    
    # 等比缩放
    ratio = (1 / ah) if ah > aw else 1 / aw
    resize_image = cv2.resize(image, (0, 0), fx=ratio, fy=ratio)
    result[:resize_image.shape[0], :resize_image.shape[1], :] = resize_image
    return result



def resize_show(image, size: tuple[int, int] = (20, 20), show_sec: int = 2) -> np.ndarray:
    resize_image = resize(image.copy(), size=size)
    
    plt.figure(dpi=120)
    for i, (image, title) in enumerate(zip([image, resize_image], ['original', 'resize'])):
        plt.subplot(121 + i)
        if image.shape[2] == 1:
            plt.imshow(image[:, :, 0], cmap='gray')
        elif image.shape[2] == 3:
            # bgr to  rgb
            b, g, r = cv2.split(image)
            plt.imshow(cv2.merge([r, g, b]))
        else:
            plt.imshow(image)
        plt.title(f'{title} {image.shape}')
    
    print(f'{show_sec}秒后将关闭plt窗口')
    plt.ion()
    plt.pause(show_sec)
    plt.close()


if __name__ == '__main__':
    original_image = np.full((40, 60, 3), 255, dtype=np.uint8)
    h, w = original_image.shape[:2]
    h_slice = slice(h // 2 - 1, h // 2 + 2)
    w_slice = slice(w // 2 - 1, w // 2 + 2)

    original_image[h_slice, w_slice, :] = 0

    resize_show(original_image)