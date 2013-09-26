#ifndef GF2_LDPC_BMP_INCLUDE
#define GF2_LDPC_BMP_INCLUDE


#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;

/***********************�����Ķ���***********************************/
extern unsigned char* pBmpBuf;  //����ͼ�����ݵ�ָ��
extern int bmpWidth;   //ͼ��Ŀ��
extern int bmpHeight;   //ͼ��ĸ߶�
extern RGBQUAD* pColorTable;   //��ɫ��ָ��
extern int biBitCount;   //ͼ�����ͣ�����λ��

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
