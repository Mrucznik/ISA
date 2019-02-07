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
    # Our operations on the frame come here
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
    cv2.line(gray,(80,60),(80,180),(255,255,255),3)
    cv2.line(gray,(80,180),(240,180),(255,255,255),3)
    cv2.line(gray,(240,180),(240,60),(255,255,255),3)
    cv2.line(gray,(240,60),(80,60),(255,255,255),3)
    cv2.circle(gray,(165,120),60,(255,255,255),3)
    # Display the resulting frame
    cv2.imshow('frame',frame)
    cv2.imshow('gray',gray)
    if cv2.waitKey(20) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()

