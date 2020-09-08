import sys
import os

import cv2
import json
import numpy as np
import retinex
from pprint import pprint

with open('config.json', 'r') as f:
    config = json.load(f)

img = cv2.imread('./data/input_0_sel.png')

hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
hue, sat, val = cv2.split(hsv)

val_float = np.float64(val) + 1.0
val_float = retinex.singleScaleRetinex(val_float, 80)
val_float = (val_float - np.min(val_float)) / \
            (np.max(val_float) - np.min(val_float)) * \
            255

val_float = np.uint8(np.minimum(np.maximum(val_float, 0), 255))

print("HSV shape: ", len(hsv))
#pprint(hsv)
print(hue.size)
print(sat.size)
print(val.size)
print(val_float.size)

#print(hsv[..., 0].depth())
#print(hsv[..., 1].depth())
#print(hsv_2nd_ch.depth())

final_hsv = cv2.merge([hue, sat, val_float])
final = cv2.cvtColor(final_hsv, cv2.COLOR_HSV2BGR)

cv2.imshow('orig', img)
cv2.imshow('hsv', hsv)
cv2.imshow('hsv[2] - brightness', val)
cv2.imshow('final hsv', final_hsv)
cv2.imshow('Final', final)

cv2.imwrite('hsv-brightness.png', val)
cv2.imwrite('hsv-corrected.png', final_hsv)
cv2.imwrite('brightness-corrected.png', final)

img_combined = np.hstack((cv2.cvtColor(val, cv2.COLOR_GRAY2BGR), final_hsv, final))
cv2.imwrite("three-in-one-hsv.png", img_combined)

cv2.waitKey(0)
