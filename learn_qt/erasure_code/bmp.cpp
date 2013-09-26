#include "bmp.h"

/****************************************************************************
读取图像的位图数据、宽度、高度、颜色表及像素位数，并存放在全局变量中
*****************************************************************************/
bool readBmp(char* bmpName)
{
 FILE* fp = fopen(bmpName,"rb");          //以二进制读的方式打开指定的图像文件
 if(fp == 0) return 0;

 //跳过位图文件头
 fseek(fp,sizeof(BITMAPFILEHEADER),0);

 //定义位图信息头结构变量，读取位图信息头进内存，存放在变量infoHead中
 BITMAPINFOHEADER infoHead;

 fread(&infoHead,sizeof(BITMAPINFOHEADER),1,fp);

 bmpWidth = infoHead.biWidth;
 bmpHeight = infoHead.biHeight;
 biBitCount = infoHead.biBitCount;

 //定义变量，计算图像每行像素所占的字节数（必须为４的倍数）
 //如果不足4的倍数，需要加上3保证足以容纳4的倍数
 int lineByte = (bmpWidth * biBitCount/8 + 3)/4 * 4;

 //灰度图像有颜色表，且颜色表为256
 if(biBitCount == 8)
 {
  //申请颜色表所需要的空间，读颜色表进内存
  pColorTable = new RGBQUAD[256];
  fread(pColorTable,sizeof(RGBQUAD),256,fp);
 }

 //申请位图数据所需要的空间，读位图数据进内存
 pBmpBuf = new unsigned char[lineByte * bmpHeight];
 fread(pBmpBuf,1,lineByte * bmpHeight,fp);
 fclose(fp);
 return 1;
}

/***************************************************************************************************
                                     将指定数据写到文件中
***************************************************************************************************/
bool saveBmp(char* bmpName, unsigned char* imgBuf, int width, int height,
    int biBitCount, RGBQUAD* pColorTable)
{
 //如果位图数据指针为0，则没有数据输入
 if (!imgBuf)
  return 0;

 //颜色表大小，以字节为单位：灰度图像为1024;彩色图像为0
 int colorTablesize = 0;
 if(biBitCount == 8)
  colorTablesize = 1024;

 //待存储图像数据每行字节数为4的倍数
 int lineByte = (width * biBitCount/8 + 3)/4 * 4;

 //以二进制写的方式打开文件
 FILE* fp = fopen(bmpName,"wb");
 if(fp == 0) return 0;

 //申请位图文件头结构变量，填写文件头信息
 BITMAPFILEHEADER fileHead;
 fileHead.bfType = 0x4D42;   // bmp 类型
 
 //bfSize是图像文件4个部分之和
 fileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
  + colorTablesize + lineByte * height;

 fileHead.bfReserved1 = 0;
 fileHead.bfReserved2 = 0;

 //bfOffBits是图像文件前3个部分所需空间之和
 fileHead.bfOffBits = 54 + colorTablesize;

 //写文件头进文件
 fwrite(&fileHead,sizeof(BITMAPFILEHEADER),1,fp);

 //申请位图信息头结构变量，填写信息头信息
 BITMAPINFOHEADER infoHead;

 infoHead.biBitCount = biBitCount;
 infoHead.biClrImportant = 0;
 infoHead.biClrUsed = 0;
 infoHead.biCompression = 0;
 infoHead.biHeight = height;
 infoHead.biPlanes = 1;
 infoHead.biSize = 40;
 infoHead.biSizeImage = lineByte * height;
 infoHead.biWidth = width;
 infoHead.biXPelsPerMeter = 0;
 infoHead.biYPelsPerMeter = 0;

 //写位图信息头进内存
 fwrite(&infoHead,sizeof(BITMAPINFOHEADER),1,fp);

 //如果灰度图像，有颜色表，写入文件
 if(biBitCount == 8)
  fwrite(pColorTable,sizeof(RGBQUAD),256,fp);

 //写位图数据进文件
 fwrite(imgBuf,height * lineByte,1,fp);
 fclose(fp);
 return 1;
}