#ifndef MyGraph_H
#define MyGraph_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <QPainter>

class MyGraph
{
public:
    MyGraph();
    MyGraph(int nodeNum);
    void paintMyGraph(QPainter &painter);

private:
    std::vector<std::pair<int, int> > nodes;
    std::map<int, int> edges;
};

#endif // MyGraph_H
