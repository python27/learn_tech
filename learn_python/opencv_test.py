import sys
import cv2
import cv2.cv as cv

image = cv.LoadImage("lena.jpg")
#image2 = image
cv.NamedWindow("mywin")
#cv.NamedWindow("yourwin")
#cv.Smooth(image,image2,cv.CV_GAUSSIAN,13)
cv.ShowImage("mywin",image)
#cv.ShowImage("yourwin",image2)
cv.WaitKey(0)
