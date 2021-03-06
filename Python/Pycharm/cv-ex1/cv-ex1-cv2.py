
#coding=utf-8

import cv2

import numpy as np

import matplotlib.pyplot as plt


image = cv2.imread("img.jpg",0)
#image=cv2.cvtColor(image,cv2.COLOR_RGB2GRAY)

lut = np.zeros(256, dtype = image.dtype )#创建空的查找表

hist= cv2.calcHist([image], #计算图像的直方图

    [0], #使用的通道

    None, #没有使用mask

    [256], #it is a 1D histogram

    [0.0,255.0])
plt.imshow(image)
plt.figure("hist")
plt.hist(hist, bins=256, density=1,edgecolor='None',facecolor='red')
minBinNo, maxBinNo = 0, 255



#计算从左起第一个不为0的直方图柱的位置
for binNo, binValue in enumerate(hist):

    print(binNo,binValue)

    if binValue != 0:

        minBinNo = binNo

        break

#计算从右起第一个不为0的直方图柱的位置

for binNo, binValue in enumerate(reversed(hist)):

    if binValue != 0:

        maxBinNo = 255-binNo

        break

print(minBinNo, maxBinNo)



#生成查找表，方法来自参考文献1第四章第2节

for i,v in enumerate(lut):

    #print(i)

    if i < minBinNo:

        lut[i] = 0

    elif i>maxBinNo:

        lut[i] = 255

    else:

        lut[i] = int(255.0*(i-minBinNo)/(maxBinNo-minBinNo)+0.5)



#计算
result = cv2.LUT(image, lut)
hist2= cv2.calcHist([image],[0], None, [256], [0.0,255.0])


cv2.imshow("Result", result)
plt.figure("hist2")
plt.hist(hist2, bins=256, density=1,edgecolor='None',facecolor='red')
plt.show()
cv2.imwrite("LutImage.jpg", result)

cv2.waitKey(0)

cv2.destroyAllWindows()
