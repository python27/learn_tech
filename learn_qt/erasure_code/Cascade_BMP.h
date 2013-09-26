/*****************************************************************
 * File: Cascade_BMP.h
 * Description: Header file for LDPC & LT Cascade encode BMP image
 * 
 * Author: Xinfeng Li (lixinfeng@zju.edu.cn)
 * Date: 2013/07/22
 *****************************************************************/
#ifndef CASCADE_BMP_INCLUDE
#define CASCADE_BMP_INCLUDE

#include <iostream>
#include <string>


using namespace std;

void cascadeEncodeBMP(char* bmpName);
void cascadeDecodeBMP(char* bmpName, double p);


#endif // CASCADE_BMP_INCLUDE