/**************************************************************************
** File Name:       helperFunction.h
** Related File:    helperFunction.cpp
** Descriptions:    some helper fucntions declaration
** Author:          Xin-Feng Li
** Version:         0.1
***************************************************************************/
#ifndef HELPER_FUNCTIONS_INCLUDED_
#define HELPER_FUNCTIONS_INCLUDED_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/**************************************************************************
 * Covert a binary 01 byte to hexadecimal expression.
 *
 * Parameters:
 *      binaryByte -- a byte of binary string
 * Returns:
 *      a hexadecimal expression of the input.
 * 
 * Example:
 *      Input  -- 00101101
 *      Output -- 2C
 **************************************************************************/
std::string binary2Hex(std::string binaryByte);


/***************************************************************************
 * find all the positions at which not all the bytes are the same.
 *
 * Parameters:
 *      lines -- all the lines get from the input file
 * Returns:
 *      the set of different byte indexes
 *
 * Example:
 *      Input -- lines
 *               lines[0]: 10101010 10101010 10101000 
 *               lines[1]: 10101010 10101001 10101000
 *               lines[2]: 10101010 10101010 10101001
 *      Output -- [8, 16] 
 *                different byte occur at byte 1 and 2
 ***************************************************************************/
std::vector<int> findDifferentBytePosition(const std::vector<std::string>& lines);

#endif // HLEPER_FUNCTIONS_INCLUDED_