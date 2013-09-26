#ifndef LT_TEXT_INCLUDE
#define LT_TEXT_INCLUDE

#include "package.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;


/*****************************************************
 * Function: inputFile2Binary 
 * Description: given a file named filename, convert the contents of the file
 *                     to binary bit stream.
 * Author: XinFeng Li
 * Date: 2013/06/07
 *****************************************************/
vector<bool> inputFile2Binary(const char* filename);


/******************************************************************
 * Function: binary2OutputFile
 * Description: convert a binary bit stream to a normal file named filename
 * Author: Xinfeng Li
 * Date: 2013/06/07
 *******************************************************************/
void binary2OutputFile(vector<bool> bvec, const char* filename);


/***************************************************************
 * Given a text file, divide it into packages, every package has 
 * the same length, in this case, every package has 1024 bytes.
 ***************************************************************/
vector<package*> dividePackage (const char* filename);


/***************************************************************
 * Print Packages 
 **************************************************************/
void printPackages(vector<package*> &v);


/****************************************************************************
 * free memory
 ****************************************************************************/
void clearPackages(vector<package*> &v);


/**********************************************
 * LT Encode algorithm 
 **********************************************/
vector<package*> encode(const vector<package*> &v);


/***********************************************************
 * Find the first One Degree Package, return the index
 ***********************************************************/
int findOneDegreePackage(vector<package*> &v, int &position);


/***************************************************************
 * find all the neighbors of the package located in index
 ***************************************************************/
vector<package*> findAllNeighbors(vector<package*> &v, int index);


/***************************************************************
 * return whether all the packages of the vector has >=1 degree.
 ***************************************************************/
bool isFull(vector<package*> &v);


/**********************************************************
 * return if all the degree of the packages is zeros.
 **********************************************************/
bool isAllDegreeZeros(const vector<package*> &v);


/**********************************************************
 * Decode the packages
 **********************************************************/
vector<package*> decode(vector<package*> &v);


/******************************************************
 * Get Current time as the file suffix.
 *****************************************************/
string getCurTimeSuffix();


/**********************************************************
 * Given the decoded packages, reconstruct the file, save
 * as filename
 **********************************************************/
void reconstructFile(vector<package*> &v, string filename);


/*********************************************************************
 * Function: LTDecodeResult
 * Description:LT decode text file
 * 
 * @filename: the source file to be decoded
 * @channelErrorRate: channel bit error rate
 *********************************************************************/
void LTDecodeResult(const char* filename, const double channelErrorRate);


/*********************************************************************
 * Function: LTEncodeResult
 * Description: LT encode text file
 *
 * Input:
 * filename --- the name of text file to be encoded
 * Output:
 * afterLTEncodeText.txt --- the file after encoding
 *
 *********************************************************************/
void LTEncodeResult(const char* filename);

#endif // LT_TEXT_INCLUDE
