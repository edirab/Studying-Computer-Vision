import cv2
import numpy as np


# Откройте изображение.
img = cv2.imread('sample.jpg')
  
# Применить логарифмическое преобразование
c = 255/(np.log(1 + np.max(img)))
log_transformed = c * np.log(1 + img)
  
# Укажите тип данных.
log_transformed = np.array(log_transformed, dtype = np.uint8)
  
# Сохранить вывод.
cv2.imwrite('log_transformed.jpg', log_transformed) 