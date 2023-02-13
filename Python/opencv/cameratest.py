import cv2

# open camera (0 for picamera)
cap = cv2.VideoCapture(0)

# set dimensions (optional)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 720)  #cv2.CAP_PROP_FRAME_WIDTH=3
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480) #cv2.CAP_PROP_FRAME_HEIGHT=4

# take frame
ret, frame = cap.read()
# write frame to file
cv2.imwrite('image.jpg', frame)
# release camera
cap.release()