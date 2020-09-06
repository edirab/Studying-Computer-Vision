import numpy as np
import imutils
import cv2

# load the image from disk
image = cv2.imread("imgs/test_marker.jpg")


rotated = imutils.rotate(image, 3)
cv2.imshow("Rotated (Problematic)", rotated)
cv2.waitKey(0)

cv2.imwrite("imgs/rotated.jpg", rotated)