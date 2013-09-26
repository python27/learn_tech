#ifndef INCLUDE_PACKAGE
#define INCLUDE_PACKAGE

#include <iostream>
#include <string>
#include <set>

using namespace std;

class package
{
public:
    package();
    ~package();

public:
    int degree;         // package degree init = 0
    set<int> neighbor;  // package XOR from packages index
    char data[1024];    // package data contents
};

#endif