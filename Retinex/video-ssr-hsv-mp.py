import numpy as np
import cv2
import json
import retinex
import time
from multiprocessing import Process, Manager

"""
Multiprocessing conversion with single scale retinex
"""

def process_image(fr_list, process_no, ret_map):
    #global frame_no

    for frame_no, frame in enumerate(fr_list):

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

        print("Processing frame No: {:04d} in process No: {}".format(frame_no, process_no))
        #out.write(final)
        #cv2.imshow("Before", frame)

        fr_list[frame_no] = final
        #cv2.imshow("After", fr_list[frame_no])
        #cv2.waitKey(0)
        frame_no += 1
    ret_map[str(process_no)] = fr_list


def main():
    with open('config.json', 'r') as f:
        config = json.load(f)

    cap = cv2.VideoCapture('./video/retinex-sample3.mp4')
    fourcc = cv2.VideoWriter_fourcc(*'XVID')
    out = cv2.VideoWriter('output-hsv-mp.avi', fourcc, 30.0, (1280, 720))

    # frame_no = 0
    start = time.time()
    print("Начало преобразования в ", start)

    frames_list = []
    #frames_list_1 = []
    #frames_list_2 = []
    #frames_list_3 = []
    #frames_list_4 = []

    """
    400 кадров для 4 потоков = 100 кадров для одного потока
    """
    frames_counter = 400
    # process_1_frame_no = 1
    # process_2_frame_no = 1
    # process_3_frame_no = 1
    # process_4_frame_no = 1

    while cap.isOpened() and frames_counter:
        ret, frame = cap.read()
        frames_list.append(frame)
        frames_counter -= 1

    """
    for i in range(0, 400, 4):
        frames_list_1.append(frames_list[i])
        frames_list_2.append(frames_list[i+1])
        frames_list_3.append(frames_list[i+2])
        frames_list_4.append(frames_list[i+3])
    """

    frames_list_1 = frames_list[0:100]
    frames_list_2 = frames_list[100:200]
    frames_list_3 = frames_list[200:300]
    frames_list_4 = frames_list[300:400]

    print("Разбивка на списки произведена")

    hash_map = Manager().dict()

    p1 = Process(target=process_image, args=(frames_list_1, 1, hash_map))
    p2 = Process(target=process_image, args=(frames_list_2, 2, hash_map))
    p3 = Process(target=process_image, args=(frames_list_3, 3, hash_map))
    p4 = Process(target=process_image, args=(frames_list_4, 4, hash_map))

    #cv2.imshow("Before", frames_list_1[0])

    p1.start()
    p2.start()
    p3.start()
    p4.start()

    #cv2.imshow("After", frames_list_1[0])
    #cv2.waitKey(0)

    p1.join()
    p2.join()
    p3.join()
    p4.join()

    end = time.time()
    print("Конвертация завершена в ", end)
    print(end - start)

    """
        frame_list_final = frames_list_1
        frame_list_final.extend(frames_list_2)
        frame_list_final.extend(frames_list_3)
        frame_list_final.extend(frames_list_4)
    """
    frame_list_final = hash_map['1']
    frame_list_final.extend(hash_map['2'])
    frame_list_final.extend(hash_map['3'])
    frame_list_final.extend(hash_map['4'])

    print("len(frame_list_final)", len(frame_list_final))
    for item in frame_list_final:
        out.write(item)

    # Release everything if job is finished
    cap.release()
    out.release()
    cv2.destroyAllWindows()


if __name__ == '__main__':
    main()
