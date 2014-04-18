/**************************************************************************
** File Name:       helperFunction.cpp
** Related File:    helperFunction.h
** Descriptions:    some helper fucntions definitions
** Author:          Xin-Feng Li
** Version:         0.1
***************************************************************************/
#include <cassert>
#include "helperFunctions.h"

/*************************************************************************
 * covert a 01 string byte to the hex expression.
 *
 * Refer to "helperFunctions.h" for the details.
 *************************************************************************/
std::string binary2Hex(std::string binaryByte)
{
    assert(binaryByte.size() == 8);
    int high4Bits =   (binaryByte[0] - '0') * 8 + (binaryByte[1] - '0') * 4 
                    + (binaryByte[2] - '0') * 2 + (binaryByte[3] - '0');
    int low4Bits =    (binaryByte[4] - '0') * 8 + (binaryByte[5] - '0') * 4 
                    + (binaryByte[6] - '0') * 2 + (binaryByte[7] - '0');
    std::string ans;
    if (high4Bits < 10)
    {
        ans.push_back(high4Bits + '0');
    }
    else
    {
        ans.push_back(high4Bits - 10 + 'A');
    }

    if (low4Bits < 10)
    {
        ans.push_back(low4Bits + '0');
    }
    else
    {
        ans.push_back(low4Bits - 10 + 'A');
    }

    return ans;
}


/*******************************************************************************
 * find all the positions at which not all the bytes are the same
 *
 * Refer to "helperFunctions.h" for the details.
 *******************************************************************************/
std::vector<int> findDifferentBytePosition(const std::vector<std::string>& lines)
{
    assert(lines.size() != 0);
    int frameNum = lines.size();
    int frameLength = lines[0].size();

    std::vector<int> ans;
    for (int index = 0; index < frameLength; index += 8)
    {
        bool isAllLinesSame = true;
        for (int i = 1; i < frameNum; ++i)
        {
            if (lines[i].substr(index, 8) != lines[0].substr(index, 8))
            {
                isAllLinesSame = false;
                break;
            }
        }

        if (!isAllLinesSame)
        {
            ans.push_back(index);
        }
    }

    return ans;
}