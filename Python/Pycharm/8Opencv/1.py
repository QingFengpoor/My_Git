import cv2
img=cv2.imread('test.png',cv2.IMREAD_COLOR)
cv2.namedWindow('image',cv2.WINDOW_NORMAL)
cv2.imshow('image',img)
cv2.waitKey(0)
cv2.destroyAllWindows()
cv2.imwrite("test.jpg",img)