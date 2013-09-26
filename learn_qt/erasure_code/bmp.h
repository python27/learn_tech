#ifndef BMP_INCLUDE
#define BMP_INCLUDE

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <set>
#include <algorithm>
#include <assert.h>
#include <windows.h>

using namespace std;
/***********************变量的定义***********************************/

extern unsigned char* pBmpBuf;  //读入图像数据的指针
extern int bmpWidth;   //图像的宽度
extern int bmpHeight;   //图像的高度
extern RGBQUAD* pColorTable;   //颜色表指针
extern int biBitCount;   //图像类型，像素位数


/****************************************************************************
读取图像的位图数据、宽度、高度、颜色表及像素位数，并存放在全局变量中
*****************************************************************************/
bool readBmp(char* bmpName);

bool saveBmp(char* bmpName, unsigned char* imgBuf, int width, int height,
    int biBitCount, RGBQUAD* pColorTable);


#endif // BMP_INCLUDE