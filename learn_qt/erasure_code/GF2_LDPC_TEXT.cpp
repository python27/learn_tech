#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "mathFunction.h"
#include "GF2_LDPC_TEXT.h"

using namespace std;

void LDPCEncodeText(const char* filename)
{
    if (filename == nullptr)
    {
        cerr << "Argument Wrong: please check your filename " << endl;
        return;
    }

    // Read file into memory
    vector<char> cvec;
    ifstream fin(filename, ios_base::in | ios_base::binary);
    if (fin.is_open())
    {
        fin.seekg(0, ios_base::end);
        size_t file_length = fin.tellg();
        fin.seekg(0, ios_base::beg);

        cvec.resize(file_length);

        if (fin.read(&cvec[0], file_length))
        {
            cout << "Read All the file contents successfully. " << endl;
        }
        else
        {
            cerr << "ERROR: Cannot Read The Whole File" << endl;
            return;
        }

        fin.close();
    }
    else
    {
        cerr << "ERROR: Cannot Open File: " << filename 
            << "Please Check your filename " << endl;
        return;
    }

    // Encode the contents in memory
    vector<char> result(cvec.begin(), cvec.end());
    for (size_t i = 0; i < result.size(); i++)
    {
        size_t cur = i;
        size_t next = (cur + 1) % result.size();
        result[i] = cvec[cur] ^ cvec[next];
    }

    // store the encoded contents into file
    ofstream fout("afterLDPCEncodeText.txt", ios_base::out | ios_base::binary);
    if (fout.is_open())
    {
        for (vector<char>::iterator iter = result.begin(); iter != result.end(); iter++)
        {
            fout << *iter;
        }
        fout.flush();
        fout.close();
    }
    else
    {
        cerr << "ERROR: Cannot Write Contens to File. " << endl;
        return;
    }



}

void LDPCDecodeText(const char* filename, double p)
{
    if (filename == nullptr)
    {
        cerr << "Argument Wrong, please Check your filename " << endl;
        return;
    }
    if (p < 0 || p > 1)
    {
        cerr << "Argument Wrong, Channel Error Rate must in [0,1] " << endl;
        return;
    }

    // Read file to memory
    vector<char> cvec;
    ifstream fin (filename, ios_base::in | ios_base::binary);
    if (fin.is_open())
    {
        fin.seekg(0, ios_base::end);
        size_t file_length = fin.tellg();
        fin.seekg(0, ios_base::beg);

        cvec.resize(file_length);

        if (fin.read(&cvec[0], file_length))
        {
            cout << "Read All the File Contents Successfully. " << endl;
        }
        else
        {
            cerr << "Cannot Extract Enough Chars " << endl;
            return;
        }
        fin.close();
    }
    else
    {
        cerr << "Wrong: Cannot Open File" 
            << "Please Check your filename" << endl;
        return;
    }
    
    // decode processing 
    vector<char> result(cvec.begin(), cvec.end());
    int package_num = cvec.size() / 1024;
    if (cvec.size() % 1024 != 0)
    {
        package_num += 1;
    }

    int error_package_num = static_cast<int>(p * package_num / 20);
    set<int> tmp = selectKfromN(error_package_num, package_num);
    for (set<int>::iterator iter = tmp.begin(); iter != tmp.end(); iter++)
    {
        int i = *iter;
        int begin = i * 1024;
        int end = (i + 1) * 1024;
        if (end > cvec.size())
        {
            end = cvec.size();
        }
        
        for (int k = begin; k < end; k++)
        {
            int next_k = (k + 1) % 1024;
            result[k] = cvec[k] ^ cvec[k+1];
        }
    }

    // store result to file
    ofstream fout("afterLDPCDecodeText.txt", ios_base::out);
    if (fout.is_open())
    {
        for (vector<char>::iterator iter = result.begin(); iter != result.end(); iter++)
        {
            fout << *iter;
        }
        fout.flush();
        fout.close();
    }
    else
    {
        cerr << "Wrong: Cannot Open File to Write. " << endl;
        return;
    }
}