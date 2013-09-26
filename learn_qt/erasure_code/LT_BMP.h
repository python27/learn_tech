#ifndef LT_BMP_INCLUDE
#define LT_BMP_INCLUDE

#include "bmp.h"
#include "mathFunction.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

/**********************************************************
 * LT Encode BMP
 * 
 * @bmpName - the name of BMP image to be encode
 **********************************************************/
void LTEncodeBMP(char* bmpName);


/****************************************************************************
 * Decode BMP image
 *
 * @bmpName: BMP image name
 * @p: channel loss rate
 ****************************************************************************/
void LTDecodeBMP(char* bmpName, double p);

#endif // LT_BMP_INCLUDE