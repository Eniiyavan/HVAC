import cv2
from persondetection import DetectorAPI
import csv
from datetime import datetime
import time
import requests
import json
import serial


global max_count3, framex3, county3, max3, avg_acc3_list, max_avg_acc3_list, max_acc3, max_avg_acc3
max_count3 = 0
framex3 = []
county3 = []
max3 = []
avg_acc3_list = []
max_avg_acc3_list = []
max_acc3 = 0
max_avg_acc3 = 0


port="COM3"
baudrate=115200
ser=serial.Serial(port, baudrate)
video = cv2.VideoCapture(0)
odapi = DetectorAPI()
threshold = 0.9

x3 = 0
previous_p=0

while True:
    check, frame = video.read()
    img = cv2.resize(frame, (800, 600))
    boxes, scores, classes, num = odapi.processFrame(img)
    person = 0
    acc = 0
    for i in range(len(boxes)):

        if classes[i] == 1 and scores[i] > threshold:
            box = boxes[i]
            person += 1
            cv2.rectangle(img, (box[1], box[0]), (box[3], box[2]), (255, 0, 0), 2)  # cv2.FILLED
            cv2.putText(img, f'P{person, round(scores[i], 2)}', (box[1] - 30, box[0] - 8),cv2.FONT_HERSHEY_COMPLEX, 0.5, (0, 0, 255), 1)  # (75,0,130),
            acc += scores[i]
            if (scores[i] > max_acc3):
                max_acc3 = scores[i]

    cv2.putText(img, f"Person Count: {person}", (10, 30),cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0, 255, 0), 2)

    cv2.imshow("Human Detection from Camera", img)
    
    p=str(person);

    
    if(previous_p!=p):
        ser.write(p.encode())
        
    key = cv2.waitKey(1)
    previous_p=p
    time.sleep(2)
    

ser.close()
