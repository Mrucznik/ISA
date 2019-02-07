#first run: sudo modprobe bcm2835-v4l2

import numpy as np
import cv2

cap = cv2.VideoCapture(0)

# cap.set(CAP_PROP_FRAME_WIDTH, 640)
# cap.set(CAP_PROP_FRAME_HEIGHT, 480)

while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()
    # Flip image
    frame = cv2.flip(frame,-1)
    # Resize image
    frame = cv2.resize(frame,(0,0),fx=0.5,fy=0.5)
    rows, cols = frame.shape[0:2]
    # Our operations on the frame come here
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    gray[0:((rows//4)*3),cols//4] = 0
    gray[(rows//4)*3,(cols//4):(cols-cols//4)] = 0
    #to nie dziala
    gray[(rows//2),0:cols] = 0
    # Display the resulting frame
    cv2.imshow('frame',frame)
    cv2.imshow('gray',gray)
    if cv2.waitKey(20) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()

