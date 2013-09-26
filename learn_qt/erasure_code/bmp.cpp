#include "bmp.h"

/****************************************************************************
��ȡͼ���λͼ���ݡ���ȡ��߶ȡ���ɫ������λ�����������ȫ�ֱ�����
*****************************************************************************/
bool readBmp(char* bmpName)
{
 FILE* fp = fopen(bmpName,"rb");          //�Զ����ƶ��ķ�ʽ��ָ����ͼ���ļ�
 if(fp == 0) return 0;

 //����λͼ�ļ�ͷ
 fseek(fp,sizeof(BITMAPFILEHEADER),0);

 //����λͼ��Ϣͷ�ṹ��������ȡλͼ��Ϣͷ���ڴ棬����ڱ���infoHead��
 BITMAPINFOHEADER infoHead;

 fread(&infoHead,sizeof(BITMAPINFOHEADER),1,fp);

 bmpWidth = infoHead.biWidth;
 bmpHeight = infoHead.biHeight;
 biBitCount = infoHead.biBitCount;

 //�������������ͼ��ÿ��������ռ���ֽ���������Ϊ���ı�����
 //�������4�ı�������Ҫ����3��֤��������4�ı���
 int lineByte = (bmpWidth * biBitCount/8 + 3)/4 * 4;

 //�Ҷ�ͼ������ɫ������ɫ��Ϊ256
 if(biBitCount == 8)
 {
  //������ɫ������Ҫ�Ŀռ䣬����ɫ����ڴ�
  pColorTable = new RGBQUAD[256];
  fread(pColorTable,sizeof(RGBQUAD),256,fp);
 }

 //����λͼ��������Ҫ�Ŀռ䣬��λͼ���ݽ��ڴ�
 pBmpBuf = new unsigned char[lineByte * bmpHeight];
 fread(pBmpBuf,1,lineByte * bmpHeight,fp);
 fclose(fp);
 return 1;
}

/***************************************************************************************************
                                     ��ָ������д���ļ���
***************************************************************************************************/
bool saveBmp(char* bmpName, unsigned char* imgBuf, int width, int height,
    int biBitCount, RGBQUAD* pColorTable)
{
 //���λͼ����ָ��Ϊ0����û����������
 if (!imgBuf)
  return 0;

 //��ɫ���С�����ֽ�Ϊ��λ���Ҷ�ͼ��Ϊ1024;��ɫͼ��Ϊ0
 int colorTablesize = 0;
 if(biBitCount == 8)
  colorTablesize = 1024;

 //���洢ͼ������ÿ���ֽ���Ϊ4�ı���
 int lineByte = (width * biBitCount/8 + 3)/4 * 4;

 //�Զ�����д�ķ�ʽ���ļ�
 FILE* fp = fopen(bmpName,"wb");
 if(fp == 0) return 0;

 //����λͼ�ļ�ͷ�ṹ��������д�ļ�ͷ��Ϣ
 BITMAPFILEHEADER fileHead;
 fileHead.bfType = 0x4D42;   // bmp ����
 
 //bfSize��ͼ���ļ�4������֮��
 fileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)
  + colorTablesize + lineByte * height;

 fileHead.bfReserved1 = 0;
 fileHead.bfReserved2 = 0;

 //bfOffBits��ͼ���ļ�ǰ3����������ռ�֮��
 fileHead.bfOffBits = 54 + colorTablesize;

 //д�ļ�ͷ���ļ�
 fwrite(&fileHead,sizeof(BITMAPFILEHEADER),1,fp);

 //����λͼ��Ϣͷ�ṹ��������д��Ϣͷ��Ϣ
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

 //дλͼ��Ϣͷ���ڴ�
 fwrite(&infoHead,sizeof(BITMAPINFOHEADER),1,fp);

 //����Ҷ�ͼ������ɫ��д���ļ�
 if(biBitCount == 8)
  fwrite(pColorTable,sizeof(RGBQUAD),256,fp);

 //дλͼ���ݽ��ļ�
 fwrite(imgBuf,height * lineByte,1,fp);
 fclose(fp);
 return 1;
}