#include "package.h"

package::package():degree(0)
{
    for (int i = 0; i < 1024; i++)
    {
        data[i] = 0;
    }
}

package::~package()
{}