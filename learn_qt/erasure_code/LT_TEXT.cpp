/*************************************************
 * File: For LT code algorithm
 * Porcess: divipackage -> encode -> decode -> 
 *          reconstructFile
 * 
 * Author: XinFeng Li (silferlee@zju.edu.cn)
 **************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "package.h"
#include "LT_TEXT.h"
#include "mathFunction.h"

using namespace std;



/***************************************************************
 * Given a text file, divide it into packages, every package has 
 * the same length, in this case, every package has 1024 bytes.
 ***************************************************************/
vector<package*> dividePackage (const char* filename)
{
    vector<package*> result;

    char buffer[1024] = {0};

    ifstream fin(filename, std::ifstream::binary);

    // get the length of the file.
    int filelength;
    if (fin)
    {
        fin.seekg(0, fin.end);
        filelength = static_cast<int>(fin.tellg());
        fin.seekg(0, fin.beg);
    }
    cout << "==Debuge==length:"<< filelength << endl;

    if (fin.is_open())
    {
        while (!fin.eof())
        {
            
            cout << "==Debug== read length: " << fin.gcount() << endl;
            cout << "==Debug== fin status: " << fin <<endl;
            if (fin.read(buffer, 1024))
            {
                package* pp = new package();
                
                //strcpy_s(pp->data, buffer);
                for (int i = 0; i < 1024; i++)
                {
                    pp->data[i] = buffer[i];
                }
                result.push_back(pp);
            }
            else
            {
                int readCnt = static_cast<int>(fin.gcount());
                cout << "==Debug==Only " << readCnt << "chars read !" <<endl;
                fin.clear();
                fin.seekg(-readCnt, fin.end);
                
                // reset buffer
                for (int i = 0; i < 1024; i++)
                {
                    buffer[i] = '\0';
                }

                fin.read(buffer, readCnt);

                package* pp = new package();
                strcpy(pp->data, buffer);

                result.push_back(pp);
                fin.setstate(ios_base::eofbit);
            }
        }

        fin.close();
    }
    else
    {
        cout << "==Debug==Cannot Open the file:" << filename << endl;
    }
    
    return result;
    
}


/***************************************************************
 * Print Packages 
 **************************************************************/
void printPackages(vector<package*> &v)
{
    vector<package*>::iterator iter = v.begin();
    for (; iter != v.end(); iter++)
    {
        cout << (*iter)->data;
    }
    
    cout << "\n==Debug==Print packages End !" <<endl;
}


/****************************************************************************
 * free memory
 ****************************************************************************/
void clearPackages(vector<package*> &v)
{
    for (vector<package*>::iterator iter = v.begin(); iter != v.end(); iter++)
    {
        delete *iter;
    }
    cout << "\n==Debug==Clear Package Memory !" << endl;
}


/**********************************************
 * LT Encode algorithm 
 **********************************************/
vector<package*> encode(const vector<package*> &v)
{
    vector<package*> result;

    int n = v.size();
    int d = 0;
    set<int> s;
    do{
        d = soliton();
        //cout << "random degree d = " << d << endl;
        while (d > n)
        {
            d = soliton();
        }

        assert(d <= n);
        s = selectKfromN(d, n);

        package* pp = new package();
        pp->degree = d;
        pp->neighbor = s;

        for (set<int>::iterator it = s.begin(); it != s.end(); it++)
        {
            for (int i = 0; i < 1024; i++)
            {
                pp->data[i] = (pp->data[i]) ^ (v[(*it)]->data[i]);
            }
        }

        result.push_back(pp);


    }while(result.size() < 2 * v.size());

    return result;
}


/***********************************************************
 * Find the first One Degree Package, return the index
 ***********************************************************/
int findOneDegreePackage(vector<package*> &v, int &position)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        if (v[i]->degree == 1)
        {
            position = i;
            set<int> s = v[i]->neighbor;
            set<int>::iterator iter = s.begin();
            return *iter;
        }
    }
    return -1000;
}


/***************************************************************
 * find all the neighbors of the package located in index
 ***************************************************************/
vector<package*> findAllNeighbors(vector<package*> &v, int index)
{
    vector<package*> result;
    for (auto iter = v.begin(); iter != v.end(); iter++)
    {
        set<int> s = (*iter)->neighbor;
        for (auto s_iter = s.begin(); s_iter != s.end(); s_iter++)
        {
            if (*s_iter == index)
            {
                result.push_back(*iter);
            }
        }
    }
    return result;
}


/***************************************************************
 * return whether all the packages of the vector has >=1 degree.
 ***************************************************************/
bool isFull(vector<package*> &v)
{
    int tmp = 0;
    for (auto iter = v.begin(); iter != v.end(); iter++)
    {
        if (((*iter)->degree) >= 1)
            tmp++;
    }
    if (tmp == v.size())
        return true;
    else
        return false;
}


/**********************************************************
 * return if all the degree of the packages is zeros.
 **********************************************************/
bool isAllDegreeZeros(const vector<package*> &v)
{
    int sum = 0;
    for (auto iter = v.begin(); iter != v.end(); iter++)
    {
        if ((*iter)->degree == 0)
        {
            sum++;
        }
    }

    if (sum == v.size())
        return true;
    else
        return false;
}


/**********************************************************
 * Decode the packages
 **********************************************************/
vector<package*> decode(vector<package*> &v)
{
    vector<package*> result;
    result.resize(v.size() / 2);

    while (1)
    {
        // result is full, all package is decoded
        if (isAllDegreeZeros(v))
        {
            break;
        }

        //cannot find one degree package, decode fail
        int position = -1;
        int index = findOneDegreePackage(v, position);
        if (index == -1000)
        {
            cout << "Cannot Find One Degree Package" << endl;
            exit(0);
        }

        // find one degree package, push into result
        result[index] = v[position];

        // all the neighbors degree - 1; and data XOR index package data
        for (auto iter = v.begin(); iter != v.end(); iter++)
        {
            size_t isErased = (*iter)->neighbor.erase(index);
            if (isErased == 1)
            {
                (*iter)->degree--;
                for (int i = 0; i < 1024; i++)
                {
                    (*iter)->data[i] ^= v[index]->data[i];
                }                
            }
        }

    }
    return result;
}


/******************************************************
 * Get Current time as the file suffix.
 *****************************************************/
string getCurTimeSuffix()
{
    // get current raw time counted by seconds since 1970
    time_t rawtime = time(NULL);
    
    // covert raw time to local time
    struct tm* ltime = localtime(&rawtime);

    // since VS2010 only has no function to_string(int) but has
    // function to_string(long long), so we use long long type
    // if your compiler support c++0x perfectly, you can use int type
    long long year = ltime->tm_year + 1900; 
    long long month = ltime->tm_mon + 1;
    long long day = ltime->tm_mday;
    long long hour = ltime->tm_hour;
    long long min = ltime->tm_min;
    long long sec = ltime->tm_sec;

    string curTime("");
    curTime = "_" + to_string(year) + "0" + to_string(month)
        + "" + to_string(day) + "_" + to_string(hour) + "h" +
        to_string(min) + "m" + to_string(sec);
    return curTime;
}


/**********************************************************
 * Given the decoded packages, reconstruct the file, save
 * as filename
 **********************************************************/
void reconstructFile(vector<package*> &v, string filename)
{
    string tmp_filename = filename + ".txt";

    ofstream fout (tmp_filename.c_str(), ofstream::out);

    vector<package*>::iterator iter = v.begin();
    for (; iter != v.end() - 1; iter++)
    {

        for (int i = 0; i < 1024; i++)
        {
            fout << (*iter)->data[i];
        }

    }

    fout << (*iter)->data;
    fout.close();
}


/*********************************************************************
 * Function: LTDecodeResult
 * Description:LT decode text file
 * 
 * @filename: the source file to be decoded
 * @channelErrorRate: channel bit error rate
 *********************************************************************/
void LTDecodeResult(const char* filename, const double channelErrorRate)
{
    if (filename == nullptr || filename == NULL)
    {
        cerr << "Parameter Error: " << filename << "Cannot be NULL" << endl;
        return ;
    }
    if (channelErrorRate < 0 || channelErrorRate > 1)
    {
        cerr << "Parameter Error:" << "channel Error Rate must in (0,1)" <<endl;
        return;
    }
    
    vector<string> vecstr;
    
    // read the text contents, store in vector<string> vecstr;
    ifstream fin(filename, ios_base::in);
    if (fin.is_open())
    {
        char* buffer = new char[1024];
        while (fin.read(buffer, 1024))
        {
            string s(buffer);
            vecstr.push_back(s);
        }
       
        string s(buffer, fin.gcount());
        vecstr.push_back(s);

        for (auto iter = vecstr.begin(); iter != vecstr.end(); iter++)
        {
            cout << *iter;
        }

        delete[] buffer;
        fin.close();
    }
    else
    {
        cerr << "Cannot open file:" << filename << endl;
        return;
    }

    // select some blocks to unrecovery
    int n = vecstr.size();
    int numUnrecoveryBlocks = static_cast<int>(channelErrorRate * n / 50.0);
    set<int> indexUnrecoveryBlocks = selectKfromN(numUnrecoveryBlocks, n);

    for (set<int>::iterator it = indexUnrecoveryBlocks.begin(); it 
        != indexUnrecoveryBlocks.end(); it++)
    {
        int i = *it;
        string curString;
        string preString(vecstr[(i-1+n)%n]);
        string nextString(vecstr[(i+1)%n]);

        // select Pre-block and Next-block, put XOR result into curString
        int minSize = preString.size() < nextString.size() ? preString.size():nextString.size();
        curString.resize(minSize);
        int k = 0;
        for (k = 0; k < minSize; k++)
        {
            curString[k] = preString[k] ^ nextString[k];
        }
        if (k >= preString.size())
        {
            curString.append(nextString, minSize, nextString.size()-minSize);
        }
        else 
        {
            curString.append(preString, minSize, preString.size()-minSize);
        }

        // put vec[i] XOR result.
        vecstr[i] = curString;
    }

    // open a new file to store the decode result
    ofstream fout("afterLTDecodeText.txt", ios_base::out);
    if (fout.is_open())
    {
        // operate fout to write the decode result
        for (auto iter = vecstr.begin(); iter != vecstr.end(); iter++)
        {
            fout << *iter;
        }

        // close ofstream fout
        fout.close();
    }
    else
    {
        cerr << "Cannot Open File to Store LT Decode Results" << endl;
        return;
    }

}


void LTEncodeResult(const char* filename)
{
    // check argument
    if (filename == NULL)
    {
        cerr << "Argument Wrong: Unknown Filename. " << endl;
        return;
    }

    // Read file
    vector<string> svec;
    ifstream fin(filename, ios_base::in | ios_base::binary);
    if (fin.is_open())
    {
        char buffer[1024] = {0};
        while(fin.read(buffer, 1024))
        {
            string s(buffer, 1024);
            svec.push_back(s);
        }
        string s(buffer, fin.gcount());
        svec.push_back(s);

        fin.close();
    }
    else
    {
        cerr << "Cannot Open File: " << filename
            << "Please Check your file name." << endl;
        return ;
    }


    // encode Processing
    vector<string> result;
    result.resize(svec.size());
    for (int i = 0; i < svec.size(); i++)
    {
        int n = svec.size();
        string curString = svec[i];
        string preString = svec[(i-1+n) % n];
        string nextString = svec[(i+1) % n];
        int minSize = preString.size() <= nextString.size() ? preString.size() : nextString.size();
        minSize = curString.size() <= minSize ? curString.size() : minSize;

        for (int k = 0; k < minSize; k++)
        {
            curString[k] = preString[k] ^ nextString[k];
        }
        if (nextString.size() > minSize)
        {
            curString.append(nextString, minSize, curString.size() - minSize);
        }
        if (preString.size() > minSize)
        {
            curString.append(preString, minSize, curString.size() - minSize);
        }
        result[i] = curString;
    }

    ofstream fout("afterLTEncodeText.txt", ios_base::out);
    if (fout.is_open())
    {
        for (auto iter = result.begin(); iter != result.end(); iter++)
        {
            fout << *iter;
        }
        fout.flush();
        fout.close();
    }
    else
    {
        cerr << "Cannot Open file to Write." << endl;
        return;
    }
}


// main fucntion used for TDD
/*
int main()
{
    LTDecodeResult("test.txt", 0.4);

    vector<package*> v = dividePackage("test.txt");
    vector<package*> encodeResult = encode(v);
    vector<package*> decodeResult = decode(encodeResult);
    reconstructFile(decodeResult, "encodetest");
    
    // encodeResult and decodeResult point to the same memory
    // so only free once.
    clearPackages(decodeResult); 
    clearPackages(v);
    
    return 0;
}
*/
