#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>
#include "helperFunctions.h"

int main()
{
    /// program header begin, readers can ignore the block.
    std::cout << std::string(50, '*') << std::endl;
    std::cout << "*" << std::string(48, ' ') << "*" << std::endl;
    std::cout << "* " << "A different bytes index checking program" << std::string(6, ' ') << " *" << std::endl;
    std::cout << "*" << std::string(48, ' ') << "*" << std::endl;
    std::cout << "*" << std::string(48, '-') << "*" << std::endl;
    std::cout << "* Parameters:" << std::string(36, ' ') << "*" << std::endl;
    std::cout << "* \t-InputFileName" << std::string(27, ' ') << "*" << std::endl;
    std::cout << "* \t-FrameNum (LineNum)" << std::string(22, ' ') << "*" << std::endl;
    std::cout << "* \t-OutputFileName" << std::string(26, ' ') << "*" << std::endl;
    std::cout << "* Returns:" << std::string(39, ' ') << "*" << std::endl;
    std::cout << "* \t-results in OutputFileName" << std::string(15, ' ') << "*" << std::endl;
    std::cout << "*" << std::string(48, ' ') << "*" << std::endl;
    std::cout << "* Copyright(C), 2014, ShiYong" << std::string(20, ' ') << "*" << std::endl;
    std::cout << "*" << std::string(48, ' ') << "*" << std::endl;
    std::cout << std::string(50, '*') << std::endl;
    /// program header end


    std::cout << ">> Please Enter the input FileName: " << std::endl;
    std::string inputFileName;
    std::cin >> inputFileName;

    std::ifstream fin(inputFileName, std::ifstream::binary);
    if (!fin.is_open())
    {
        std::cerr << ">> Error: Cannot open file " << inputFileName << "to Read !!!\n"
                  << ">> The program will exit..." << std::endl;
        return -1;
    }
    // get the length of the file
    fin.seekg(0, fin.end);
    int fileLength = fin.tellg();
    fin.seekg(0, fin.beg);
    std::cout << ">> The file has " << fileLength << " bits (" 
              << (fileLength) / 8 << " bytes)" << std::endl;

    // split file into lines
    std::cout << ">> Please Enter the frameNum you want to split: " << std::endl;
    int frameNum = 0;
    std::cin >> frameNum;
    int frameLength = (fileLength) / frameNum;
    std::cout << ">> The file will be split into " << frameNum << " lines\n"
              << ">> Every line will contain " << frameLength / 8 << " bytes" << std::endl;
    
    // read file into vector<string> line by line
    char* buffer = new char[frameLength + 1];
    std::vector<std::string> lines(frameNum);
    for (int i = 0; i < frameNum; ++i)
    {
        fin.read(buffer, frameLength);
        buffer[frameLength] = '\0';
        lines[i] = std::string(buffer);
    }
    delete[] buffer;
    buffer = NULL;
    fin.close();

    // find differet bytes indexes
    std::vector<int> diffIndexes = findDifferentBytePosition(lines);
    if (diffIndexes.size() == 0)
    {
        std::cout << "\n>> Congratulations, all lines are the same !" << std::endl;
        return 0;
    }

    // output
    std::cout << ">> Please Enter the output fileName: " << std::endl;
    std::string outputFileName;
    std::cin >> outputFileName;
    std::ofstream fout (outputFileName, std::ofstream::out);
    if (!fout.is_open())
    {
        std::cerr << ">> Cannot open file " << outputFileName << " to write !!!\n"
                  << ">> The program will exit..." << std::endl;
       return -1; 
    }
    
    fout << "DiffByte";
    for (int i = 0; i < frameNum; ++i)
    {
        fout << "\tLine " << i + 1;
    }
    fout << std::endl;

    std::string hexExpression;
    for (int i = 0; i < diffIndexes.size(); ++i)
    {
        int index = diffIndexes[i];
        fout << index / 8 + 1;
        for (int row = 0; row < frameNum; ++row)
        {
            hexExpression = binary2Hex(lines[row].substr(index, 8));
            fout << "\t" << hexExpression;
        }
        fout << std::endl;
    }
    fout.close();

    std::cout << ">> The process is done successfully !\n"
              << ">> Please open the file " << outputFileName 
              << " to find the result" << std::endl;
    return 0;
}

