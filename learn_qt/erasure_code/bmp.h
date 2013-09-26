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
/***********************�����Ķ���***********************************/

extern unsigned char* pBmpBuf;  //����ͼ�����ݵ�ָ��
extern int bmpWidth;   //ͼ��Ŀ��
extern int bmpHeight;   //ͼ��ĸ߶�
extern RGBQUAD* pColorTable;   //��ɫ��ָ��
extern int biBitCount;   //ͼ�����ͣ�����λ��


/****************************************************************************
��ȡͼ���λͼ���ݡ���ȡ��߶ȡ���ɫ������λ�����������ȫ�ֱ�����
*****************************************************************************/
bool readBmp(char* bmpName);

bool saveBmp(char* bmpName, unsigned char* imgBuf, int width, int height,
    int biBitCount, RGBQUAD* pColorTable);


#endif // BMP_INCLUDE