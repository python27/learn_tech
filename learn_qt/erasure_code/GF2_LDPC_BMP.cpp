#include "bmp.h"
#include "mathFunction.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <set>
#include <algorithm>
#include <assert.h>
#include <windows.h>
#include "GF2_LDPC_BMP.h"

using namespace std;

/***********************�����Ķ���***********************************/

unsigned char* pBmpBuf;  //����ͼ�����ݵ�ָ��
int bmpWidth;   //ͼ��Ŀ��
int bmpHeight;   //ͼ��ĸ߶�
RGBQUAD* pColorTable;   //��ɫ��ָ��
int biBitCount;   //ͼ�����ͣ�����λ��

/********************************************************************
 * LDPC EnCode BMP
 * @bmpName - the name of bmp image you want to encode
 ********************************************************************/
void LDPCEncodeBMP(char* bmpName)
{

 //����ָ��BMP�ļ����ڴ�
 readBmp(bmpName);

 //���ͼ�����Ϣ
 cout<<"width="<<bmpWidth<<" height="<<bmpHeight<<" BitCount="<<biBitCount<<endl;

 //ÿ���ֽ���
 int lineByte = (bmpWidth * biBitCount/8 + 3)/4 * 4;

 //ѭ����������
 int m=0,n=0,pixCount=0;

 //����ı����ص��ı��ļ�
 ofstream outfile("BMPPixels.txt",ios_base::in | ios_base::trunc );

 if(biBitCount == 8)   //�Ҷ�ͼ��
 {
  //��ͼ������Ϸ���1/4��Ϊ��ɫ
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

 else if(biBitCount == 24)     //��ɫͼ��
 {
  for(int i=0;i<bmpHeight;i++)
  {
    
    int preRow = (i - 1 + bmpHeight) % bmpHeight;

   // given every pixel, operate XOR.
   for(int j=0;j<bmpWidth;j++)
   {
    
    int tmpB = 0; int tmpR = 0; int tmpG = 0;
    tmpB = (*(pBmpBuf + preRow * lineByte + j * 3 + 0)) ^ (*(pBmpBuf + i * lineByte + j * 3 + 0));
    tmpG = (*(pBmpBuf + preRow * lineByte + j * 3 + 1)) ^ (*(pBmpBuf + i * lineByte + j * 3 + 1));
    tmpR = (*(pBmpBuf + preRow * lineByte + j * 3 + 2)) ^ (*(pBmpBuf + i * lineByte + j * 3 + 2));

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
  cout<<"�ܵ����ظ���Ϊ:"<<n<<endl;
 }

 //��ͼ�����ݴ���
 char* writePath = "afterLDPCEncodeImage.bmp";

 //ͼƬ������ٴ洢
 saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);

 delete[] pBmpBuf;
 if(biBitCount == 8)
  delete[] pColorTable;

 outfile.close();
}


/****************************************************************************
 * Decode BMP image
 *
 * @bmpName: BMP image name
 * @p: channel loss rate
 ****************************************************************************/
void LDPCDecodeBMP(char* bmpName, double p)
{
    // check argument
    if (bmpName == NULL)
    {
        cerr << "please enter an BMP name" <<endl;
        return;
    }
    if (p <= 0 || p >= 1)
    {
        cerr << "The channel loss rate must between (0,1)" << endl;
    }
    assert(p > 0 && p < 1);

    //����ָ��BMP�ļ����ڴ�
    readBmp(bmpName);

    //ÿ���ֽ���
    int lineByte = (bmpWidth * biBitCount/8 + 3)/4 * 4;

    //ѭ����������
    int m = 0;
    int n = 0;
    int pixCount = 0;

    int rowToSmoothNum = static_cast<int>(p * bmpHeight / 50);  // the number of rows to be smoothed
    // select these rows randomly
    set<int> rowToSmoothIndexs = selectKfromN(rowToSmoothNum, bmpHeight);


    if (biBitCount == 8)   //�Ҷ�ͼ��
    {
        for(int i = bmpHeight/2; i < bmpHeight; i++)
        {
            for(int j = lineByte/2; j < lineByte; j++)
            {
                m=*(pBmpBuf + i*lineByte + j) = 0;
            }
        }
    }

    else if(biBitCount == 24)     //��ɫͼ��
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

         //��ͼ�����ݴ���
         char* writePath = "afterLDPCDecodeImage.bmp";

         //ͼƬ������ٴ洢
         saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);

         delete[] pBmpBuf;
         if(biBitCount == 8)
         {
            delete[] pColorTable;
         }
}

/*
int main()
{
    LDPCEncodeBMP("lena.bmp");
    LDPCDecodeBMP("lena.bmp", 0.20);
    return 0;
}
*/
