import cv2
import numpy as np
from ultralytics import YOLO

# Load YOLOv8 model
model = YOLO(rf"./yolov11_tools.pt")
model.fuse()

# Define detection parameters
conf_thres = 0.01
iou_thres = 0.10
max_det = 100
classes = (list(range(1)))
device = "cpu"

# Load video 
video = cv2.VideoCapture("./tools_ex_2.mp4")

# iterate through each frame
while True:
    # Load frame from video
    ret,frame = video.read()
    frame = cv2.resize(frame, (640, 640))
    
    # Make prediction over frame
    results = model.track(  source=frame,
                            conf=conf_thres,
                            max_det=max_det,
                            persist=True)
    
    # Plot Values
    plotted_image = results[0].plot()
    # Get prediction values
    bounding_box = results[0].boxes.xywh
    classes = results[0].boxes.cls

    cv2.imshow("frame",plotted_image)
    cv2.waitKey(25)

