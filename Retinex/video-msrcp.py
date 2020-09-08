import numpy as np
import cv2
import json
import retinex
import time


with open('config.json', 'r') as f:
    config = json.load(f)

cap = cv2.VideoCapture('./video/retinex-sample3.mp4')

# Define the codec and create VideoWriter object
fourcc = cv2.VideoWriter_fourcc(*'XVID')
out = cv2.VideoWriter('output.avi',fourcc, 30.0, (1280,720))
#out = cv2.VideoWriter('./video/output.avi', -1, 20.0, (640,480))

frame_no = 0
start = time.time()
print("Начало преобразования в ", start)

while cap.isOpened():
    ret, frame = cap.read()

    if ret:
        out_msrcp = retinex.MSRCP(
            frame,
            config['sigma_list'],
            config['low_clip'],
            config['high_clip']
        )

        print("Processing frame No: {:04d}".format(frame_no))
        out.write(out_msrcp)
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