#include "graph.h"
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <QPainter>
#include <map>
#include <vector>

MyGraph::MyGraph():nodes(20)
{
    int nodeNum = 20;
    srand(time(NULL));
    for (int i = 0; i < nodeNum; ++i)
    {
        int x = rand() % 600;;
        int y = rand() % 600;;
        nodes[i].first = x;
        nodes[i].second = y;
    }

    // generate the random edges
    for (int i = 0; i < nodeNum; ++i)
    {
        int s = rand() % nodeNum;
        int e = rand() % nodeNum;
        edges[s] = e;
    }

}


MyGraph::MyGraph(int nodeNum):nodes(nodeNum)
{
    // generate the random points
    srand(time(NULL));
    for (int i = 0; i < nodeNum; ++i)
    {
        int x = rand() % 600;;
        int y = rand() % 600;;
        nodes[i].first = x;
        nodes[i].second = y;
    }

    // generate the random edges
    for (int i = 0; i < nodeNum; ++i)
    {
        int s = rand() % nodeNum;
        int e = rand() % nodeNum;
        edges[s] = e;
    }

}


void MyGraph::paintMyGraph(QPainter &painter)
{
    int nodeNum = nodes.size();
    for (int i = 0; i < nodeNum; ++i)
    {
        painter.drawEllipse(nodes[i].first, nodes[i].second, 5, 5);
    }

    for (std::map<int, int>::iterator it = edges.begin(); it != edges.end(); ++it)
    {
        int s = it->first;
        int e = it->second;
        painter.drawLine(nodes[s].first, nodes[s].second, nodes[e].first, nodes[e].second);
    }
}
