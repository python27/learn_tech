#include <iostream>
#include <string>
#include "message.h"
using namespace std;

int main()
{
    RequestMsg m(3, 2);
    m.appendPath(10);
    m.appendPath(11);
    m.printMessage();
    return 0;
}
