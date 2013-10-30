#include <iostream>
#include <string>
#include "graph.h"

using std::cout;
using std::endl;

int main()
{
    Graph::setWidthHeight(100, 100);
    Graph::Graph g(10, 50);
    g.printGraph();
    return 0;
}
