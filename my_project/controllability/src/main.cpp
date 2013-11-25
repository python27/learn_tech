#include "mclmcr.h"
#include "matrix.h"
#include "mclcppclass.h"
#include "controllib.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{

    // init controllib
    if (!controllibInitialize())
    {
        cout << "could not initialize controllib" << endl;
        return -1;
    }

    // set 1 * 1 matrix, all data in the matrix is double
    mwArray mwA(2, 2, mxDOUBLE_CLASS);
    mwArray mwND(1, 1, mxDOUBLE_CLASS);
    mwArray mwEV(1, 1, mxDOUBLE_CLASS);
    
    double *nd = new double(1.5);
    double *ev = new double(1.5);
    double *a = new double[4];
    a[0] = 0;
    a[1] = 1;
    a[2] = 1;
    a[3] = 0;

    // set nwA matrix values with array a;
    mwA.SetData(a, 4);
    mwND.SetData(nd, 1);
    mwEV.SetData(ev, 1);
    
    // call the controllib function
    getDriverNodeNumber(2, mwND, mwEV, mwA); 
    mwEV.GetData(ev, 1);
    mwND.GetData(nd, 1);

    // get Data
    cout << "nd: " << *nd << endl;
    cout << "eigenvalue:"  << *ev << endl;


    delete[] a;
    delete nd;
    delete ev;

    // terminal the lib
    controllibTerminate();
    mclTerminateApplication();
    return 0;
}
