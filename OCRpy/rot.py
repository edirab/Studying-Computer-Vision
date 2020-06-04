import numpy as np
import imutils
import cv2

# load the image from disk
image = cv2.imread("test_marker.jpg")

# loop over the rotation angles
for angle in np.arange(0, 360, 15):
    rotated = imutils.rotate(image, angle)
    cv2.imshow("Rotated (Problematic)", rotated)
    cv2.waitKey(0)

# loop over the rotation angles again, this time ensuring
# no part of the image is cut off
for angle in np.arange(0, 360, 15):
    rotated = imutils.rotate_bound(image, angle)
    cv2.imshow("Rotated (Correct)", rotated)
    cv2.waitKey(0)
