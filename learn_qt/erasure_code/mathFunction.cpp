#include "mathFunction.h"
#include <cstdlib>  // srand, rand
#include <ctime>    // time
#include <random>   // random_shuffle. Waning: Need complier support  C++0x

/**************************************************************
 * selecet a degree randomly from a solotion degree distribution
 * given prob, return a degree.
 **************************************************************/
int prob2degree(double p)
{
    if (p <= 0.1)
        return 1;
    else if (p <= 0.6)
        return 2;
    else if (p <= 0.766667)
        return 3;
    else if (p <= 0.85)
        return 4;
    else if (p <= 0.9)
        return 5;
    else if (p <= 0.933333)
        return 6;
    else if (p <= 0.957143)
        return 7;
    else if (p <= 0.975)
        return 8;
    else if (p <= 0.988889)
        return 9;
    else
        return 10;
}


/***********************************************************
 *select degree d randomly according to soliton distribution
 ***********************************************************/
int soliton()
{
    random_device rd;
    mt19937 gen(rd());
    
    uniform_real_distribution<double> distribution(0.0, 1.0);

    double p = distribution(gen);
    int d = prob2degree(p);
    return d;
}

/************************************************************
 * Helper Function. Used as Random Number Generator in C++0x
 * which is a functional object used by STL library
 * | random_shuffle |
 ************************************************************/
int myrandom(int i)
{
    return rand() % i;
}


/**********************************************************
 * random select K numbers from [0,1,2,...,N-1]
 **********************************************************/
set<int> selectKfromN(int k, int N)
{
    assert(k <= N);
    vector<int> v;
    for (int i = 0; i < N; i++) // 0 1 2 ... N-1
    {
        v.push_back(i);
    }

    srand((unsigned)time(NULL)); // shuffle seed initialization
    random_shuffle(v.begin(), v.end(), myrandom);

    set<int> s;
    for (int i = 0; i < k; i++)
    {
        s.insert(v[i]);
    }

    return s;

}
