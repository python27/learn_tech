#include "Cascade_BMP.h"
#include "bmp.h"
#include "mathFunction.h"
#include <iostream>
#include <string>
#include <cstdlib>  // srand, rand
#include <ctime>    // time
#include <random>   // random_shuffle
#include <algorithm>    // shuffle

using namespace std;

/********************************************************
 * Function: LT_LDPC_Cascade Encode BMP
 *
 * Input:
 * bmpName --- the name of bmp image to be encode
 * 
 * Output: No returns.
 * give the encoded bmp image saved as bmp file.
 * 
 * Usage:
 * cascadeEncodeBMP("lena.bmp");
 ********************************************************/
void cascadeEncodeBMP(char* bmpName)
{
    //读入指定BMP文件进内存
 readBmp(bmpName);

 //输出图像的信息
 cout<<"width = "<<bmpWidth<<" height = "<<bmpHeight<<" BitCount = "<<biBitCount<<endl;

 //每行字节数
 int lineByte = (bmpWidth * biBitCount/8 + 3)/4 * 4;

 //循环变量定义
 int m=0,n=0,pixCount=0;

 //输出改变像素的文本文件
 ofstream outfile("BMPPixels.txt",ios::in | ios::trunc );

 if(biBitCount == 8)   //灰度图像
 {
  //把图像的右上方的1/4变为黑色
  for(int i=bmpHeight/2;i<bmpHeight;i++)
  {
   for(int j=lineByte/2;j<lineByte;j++)
   {
    m=*(pBmpBuf + i*lineByte + j) = 0;
    outfile<<m<<" ";
    pixCount++;
    if(pixCount%8 == 0)
     outfile<<endl;
   }
  }
 }

 if(!outfile)
  cout<<"Open error!"<<endl;

 else if(biBitCount == 24)     //彩色图像
 {
  for(int i=0;i<bmpHeight;i++)
  {
    
    int preRow = (i - 1 + bmpHeight) % bmpHeight;
    set<int> tmpS = selectKfromN(10, bmpHeight);

   // given every pixel, operate XOR.
   for(int j = 0; j < bmpWidth; j++)
   {    
    int tmpB = 0; int tmpR = 0; int tmpG = 0;

    tmpB = (*(pBmpBuf + preRow * lineByte + j * 3 + 0)) ^ (*(pBmpBuf + i * lineByte + j * 3 + 0));
    tmpG = (*(pBmpBuf + preRow * lineByte + j * 3 + 1)) ^ (*(pBmpBuf + i * lineByte + j * 3 + 1));
    tmpR = (*(pBmpBuf + preRow * lineByte + j * 3 + 2)) ^ (*(pBmpBuf + i * lineByte + j * 3 + 2));

    // first using LT encode method, encode.
    for (set<int>::iterator it = tmpS.begin(); it != tmpS.end(); it++)
    {
       tmpB ^= (*(pBmpBuf +  (*it) * lineByte + j * 3 + 0));
       tmpG ^= (*(pBmpBuf +  (*it) * lineByte + j * 3 + 1));
       tmpR ^= (*(pBmpBuf +  (*it) * lineByte + j * 3 + 2));
    }


    //----------B----------
    m = *(pBmpBuf + i * lineByte + j * 3 + 0) = tmpB;  // B
    outfile << m << " ";
    pixCount++;
    if (pixCount % 8 == 0)
        outfile << endl;

    //----------G----------
    m = *(pBmpBuf + i * lineByte + j * 3 + 1) = tmpG;   // G
    outfile << m << " ";
    pixCount++;
    if (pixCount % 8 == 0)
        outfile << endl;

    //----------R-----------
    m = *(pBmpBuf + i * lineByte + j * 3 + 2) = tmpR; // R
    outfile << m << " ";
    pixCount++;
    if (pixCount % 8 == 0)
        outfile << endl;

    n++;
   }
  }
  cout<<"总的像素个数为:"<<n<<endl;
 }

 // 将图像数据存盘
 char* writePath = "afterCascadeEncodeImage.bmp";

 // 图片处理后再存储
 saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);

 delete[] pBmpBuf;
 if(biBitCount == 8)
  delete[] pColorTable;

}


/**************************************************
 * LT & LDPC Cascade erasure code, decode algorithm
 * 
 * Input:
 * bmpName --- the name of Bmp image to be decode
 * p --- Channel Error Rate, must be in [0, 1]
 *
 * Output:
 * None, create the decoded BMP image.
 *
 * Usage:
 * cascadeDecodeBMP("lena.bmp", 0.2)
 **************************************************/
void cascadeDecodeBMP(char* bmpName, double p)
{
    if (bmpName == NULL)
    {
        cerr << "Cannot find BMP image files !" << endl;
        return;
    }
    if (p <= 0 || p > 1)
    {
        cerr << "Wrong Channel Error Rate, please check your argument !" << endl;
        return;
    }

    //读入指定BMP文件进内存
    readBmp(bmpName);

    //每行字节数
    int lineByte = (bmpWidth * biBitCount/8 + 3) / 4 * 4;

    //循环变量定义
    int m = 0;
    int n = 0;
    int pixCount = 0;

    int rowToSmoothNum = static_cast<int>(p * bmpHeight / 200);  // the number of rows to be smoothed, divide 
                                                                 // the enlarge coefficient
    set<int> rowToSmoothIndexs = selectKfromN(rowToSmoothNum, bmpHeight); // select these rows randomly

    if (biBitCount == 8)   //灰度图像
    {
        for(int i = bmpHeight/2; i < bmpHeight; i++)
        {
            for(int j = lineByte/2; j < lineByte; j++)
            {
                m=*(pBmpBuf + i*lineByte + j) = 0;
            }
        }
    }
    else if(biBitCount == 24)     //彩色图像
    {
        for(set<int>::iterator it = rowToSmoothIndexs.begin();it != rowToSmoothIndexs.end();it++)
        {
            // for every selected row, get the pre-row and next-row
            int i = *it;
            int preLine = (i - 1 + bmpHeight) % bmpHeight;
           
           for(int j=0;j<bmpWidth;j++)
           {
            int tmpB = *(pBmpBuf + preLine * lineByte + j * 3 + 0) ^ *(pBmpBuf + i * lineByte + j * 3 + 0); 
            int tmpR = *(pBmpBuf + preLine * lineByte + j * 3 + 1) ^ *(pBmpBuf + i * lineByte + j * 3 + 1);
            int tmpG = *(pBmpBuf + preLine * lineByte + j * 3 + 2) ^ *(pBmpBuf + i * lineByte + j * 3 + 2);

            //----------B----------
            m = *(pBmpBuf + i * lineByte + j * 3 + 0) = tmpB;  // B

            //----------G----------
            m = *(pBmpBuf + i * lineByte + j * 3 + 1) = tmpG;   // G

            //----------R-----------
            m = *(pBmpBuf + i * lineByte + j * 3 + 2) = tmpR; // R
           }
          }
     }

         //将图像数据存盘
         char* writePath = "afterCascadeDecodeImage.bmp";

         //图片处理后再存储
         saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);

         delete[] pBmpBuf;
         if(biBitCount == 8)
         {
            delete[] pColorTable;
         }
}