import cv2
import numpy as np

# Откройте изображение.
img = cv2.imread('sample.jpg')
  
# Попробуем 4 значения гаммы.
for gamma in [0.1, 0.5, 1.2, 2.2]:

    # Применить гамма-коррекцию.
    gamma_corrected = np.array(255*(img / 255) ** gamma, dtype = 'uint8')
  
    # Сохранить отредактированные изображения.
    cv2.imwrite('gamma_transformed'+str(gamma)+'.jpg', gamma_corrected) 