import time
import sys
from picamera.array import PiRGBArray
from picamera import PiCamera
import cv2

print("Python version: {}".format(sys.version))

camera = PiCamera()
camera.resolution = (640, 480)
camera.framerate = 30
rawCapture = PiRGBArray(camera, size=(640, 480))

time.sleep(2)

for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
    image = frame.array
    cv2.imshow("Image", image)
    key = cv2.waitKey(1) & 0xFF

    rawCapture.truncate(0)
    
    if key == ord("q"):
        break
