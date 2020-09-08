import numpy as np
import cv2
import json
import retinex
import time

with open('config.json', 'r') as f:
    config = json.load(f)

cap = cv2.VideoCapture('./video/retinex-sample3.mp4')
fourcc = cv2.VideoWriter_fourcc(*'XVID')
out = cv2.VideoWriter('output-hsv.avi',fourcc, 30.0, (1280,720))

frame_no = 0
start = time.time()
print("Начало преобразования в ", start)

while cap.isOpened():
    ret, frame = cap.read()

    if ret:
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        hue, sat, val = cv2.split(hsv)

        val_float = np.float64(val) + 1.0
        val_float = retinex.singleScaleRetinex(val_float, 80)
        val_float = (val_float - np.min(val_float)) / \
                    (np.max(val_float) - np.min(val_float)) * \
                    255

        val_float = np.uint8(np.minimum(np.maximum(val_float, 0), 255))
        final_hsv = cv2.merge([hue, sat, val_float])
        final = cv2.cvtColor(final_hsv, cv2.COLOR_HSV2BGR)

        print("Processing frame No: {:04d}".format(frame_no))
        out.write(final)
        frame_no += 1

        #cv2.imshow('frame',frame)
        #cv2.imshow('frame msrcp', out_msrcp)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    else:
        break

end = time.time()
print("Конвертация завершена в ", end)
print(end - start)

# Release everything if job is finished
cap.release()
out.release()
cv2.destroyAllWindows()