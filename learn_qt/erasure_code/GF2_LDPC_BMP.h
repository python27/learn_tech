#ifndef GF2_LDPC_BMP_INCLUDE
#define GF2_LDPC_BMP_INCLUDE


#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;

/***********************变量的定义***********************************/
extern unsigned char* pBmpBuf;  //读入图像数据的指针
extern int bmpWidth;   //图像的宽度
extern int bmpHeight;   //图像的高度
extern RGBQUAD* pColorTable;   //颜色表指针
extern int biBitCount;   //图像类型，像素位数

/********************************************************************
 * LDPC EnCode BMP
 * @bmpName - the name of bmp image you want to encode
 ********************************************************************/
void LDPCEncodeBMP(char *bmpName);


/****************************************************************************
 * Decode BMP image
 *
 * @bmpName: BMP image name
 * @p: channel loss rate
 ****************************************************************************/
void LDPCDecodeBMP(char *bmpName, double p);
#endif // GF2_LDPC_BMP_INCLUDE
