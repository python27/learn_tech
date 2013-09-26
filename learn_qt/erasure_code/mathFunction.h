#ifndef MATH_FUNCTION_INCLUDE
#define MATH_FUNCTION_INCLUDE

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <set>
#include <algorithm>
#include <assert.h>
#include <windows.h>

using namespace std;

/**************************************************************
 * selecet a degree randomly from a solotion degree distribution
 * given prob, return a degree.
 **************************************************************/
int prob2degree(double p);


/***********************************************************
 *select degree d randomly according to soliton distribution
 ***********************************************************/
int soliton();


/**********************************************************
 * random select K numbers from [0,1,2,...,N-1]
 **********************************************************/
set<int> selectKfromN(int k, int N);


/**********************************************************
 * helper function, a function object, used by random_shuffle
 **********************************************************/
int myrandom(int i);

#endif //MATH_FUNCTION_INCLUDE
