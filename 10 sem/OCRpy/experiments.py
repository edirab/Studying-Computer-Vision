# https://stackoverflow.com/questions/57797400/pytesseract-fails-to-recognize-digits-from-image

#from imutils.object_detection import non_max_suppression
import numpy as np
import pytesseract
import argparse
import cv2

threshold = 180

print(cv2.__version__)

pytesseract.pytesseract.tesseract_cmd = r'C:/Program Files/Tesseract-OCR/tesseract.exe'
print(pytesseract.get_tesseract_version())

image = cv2.imread("imgs/test_marker.jpg")
image_gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
cv2.imshow('image_gray', image_gray)

kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (3,3))
close = cv2.morphologyEx(image_gray, cv2.MORPH_CLOSE, kernel)
result = close
cv2.imwrite("imgs/test_filtered.jpg", result)

cv2.imshow('result', result)
# orig = image.copy()


#img_binarized = cv2.threshold(image_gray, threshold, 255, cv2.THRESH_BINARY_INV)
# cv2.imshow('img_binarized', img_binarized)

#img_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)


# custom_oem_psm_config = r'--oem 3 --psm 6'
# print(pytesseract.image_to_string(img_rgb, custom_oem_psm_config))

# print(pytesseract.image_to_string(result, lang='rus', config='--psm 6'))
# print(pytesseract.image_to_string(image_gray, lang='rus'))
print(pytesseract.image_to_string(image, lang='rus'))

#print(pytesseract.image_to_string(img_rgb))

cv2.waitKey()