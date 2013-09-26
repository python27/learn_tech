#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "mathFunction.h"
#include "Cascade_TEXT.h"

using namespace std;

/******************************************************************
 * Function: cascadeEncodeText
 * Description: use LT & LDPC Cascade algorithm to encode Text file
 *
 * Input:
 * filename --- the name of file to be encoded
 *
 * Output:
 * None. An encoded file
 *
 * Algorithm Process:
 * store file contents into memory --> Process XOR operation --> save 
 * encoded contents into file.
 *
 * Author: Xinfeng Li (lixinfeng@zju.edu.cn)
 ********************************************************************/
void cascadeEncodeText(const char* filename)
{
    vector<char> cvec;  // store the |filename| contents into vector
    ifstream fin(filename, ios_base::in | ios_base::binary);
    if (fin.is_open())
    {
        fin.seekg(0, ios_base::end);
        long long file_length = static_cast<long long>(fin.tellg());
        fin.seekg(0, ios_base::beg);

        cvec.resize(static_cast<unsigned int>(file_length));
        if (fin.read(&cvec[0], file_length))
        {
            cout << "Read All the File Successfully." << endl;
        }
        else
        {
            cerr << "Cannot Extract Enough chars to memory." << endl;
        }
        fin.close();
    }
    else
    {
        cerr << "Cannot Open File: " << filename << endl;
        cerr << "Please Check the File Name !" << endl;
        return;
    }

    // use vector to operate XOR
    // process the full 1024Byte package
    vector<char> result;
    result.resize(cvec.size(), 0);

    int package_num = cvec.size() / 1024;
    if (cvec.size() % 1024 != 0)
    {
        package_num += 1;
    }

    for (int i = 0; i < package_num - 1; i++)
    {
        set<int> select = selectKfromN(3, package_num - 1);
        for (set<int>::iterator it = select.begin(); it != select.end(); it++)
        {
            int j = *it;
            int sbegin = i * 1024;
            int dbegin = j * 1024;
            for (int cnt = 0; cnt < 1024; cnt++)
            {
                result[sbegin++] ^= cvec[dbegin++];
            }
        }

    }

    // Process the last incomplete package
    int i = package_num - 1;
    set<int> select = selectKfromN(3, package_num);
    int remain_length = cvec.size() % 1024;
    if (remain_length == 0)
    {
        remain_length = 1024;
    }
    for (set<int>::iterator it = select.begin(); it != select.end(); it++)
    {
        int j = *it;
        int sbegin = i * 1024;
        int dbegin = j * 1024;
        for (int cnt = 0; cnt < remain_length; cnt++)
        {
            result[sbegin++] ^= cvec[dbegin++];
        }
    }

    // Write to file
    ofstream fout("afterCascadeEncodeText.txt", ios_base::out);
    if (fout.is_open())
    {
        for (size_t i = 0; i < result.size(); i++)
        {
            fout << result[i];
        }
        fout.close();
    }
    else
    {
        cout << "ERROR: Cannot Open file to Write." << endl;
        return;
    }
}


void cascadeDecodeText(const char* filename, double p)
{
    if (filename == nullptr)
    {
        cerr << "ERROR: argument Wrong, filename is NULL" << endl;
        return;
    }
    if (p < 0 || p > 1)
    {
        cerr << "ERROR: Argument Wrong! Channel Error Rate must in [0,1] " << endl;
        return;
    }

    vector<char> cvec;  // store the contents from file
    ifstream fin (filename, ios_base::in | ios_base::binary);
    if (fin.is_open())
    {
        fin.seekg(0, fin.end);
        long long file_length = static_cast<long long>(fin.tellg());
        fin.seekg(0, fin.beg);
        cvec.resize(static_cast<unsigned int>(file_length));

        if (fin.read(&cvec[0], file_length))
        {
            cout << "Read All the file Successfully." << endl;
        }
        else
        {
            cerr << "ERROR: Cannot Extract Enough chars. " << endl;
            return;
        }

        fin.close();
    }
    else
    {
        cerr << "Cannot Open File: " << filename << "to Read !" 
            << "Please Check your Filename " << endl;
        return;
    }

    int package_num = cvec.size() / 1024;
    if (cvec.size() % 1024 != 0)
    {
        package_num += 1;
    }
    int error_package_num = static_cast<int>(package_num * p / 80);
    set<int> indexs = selectKfromN(error_package_num, package_num);
    for (set<int>::iterator iter = indexs.begin(); iter != indexs.end(); iter++)
    {
        int i = *iter;
        int begin = i * 1024;
        int end = (i + 1) * 1024;
        if (end > cvec.size())
        {
            end = cvec.size();
        }
        end -= 1;
        while (begin <= end)
        {
            char tmp = cvec[begin] ^ cvec[end];
            cvec[begin] = tmp;
            cvec[end] = tmp;
            begin++;
            end--;
        }
    }


    ofstream fout ("afterCascadeDecodeText.txt", ios_base::out);
    if (fout.is_open())
    {
        for (int i = 0; i < cvec.size(); i++)
        {
            fout << cvec[i];
        }
        fout.close();
    }
    else
    {
        cerr << "Cannot Open File to Write !" << endl;
        return;
    }
}