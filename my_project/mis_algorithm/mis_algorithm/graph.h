#ifndef MIS_GRAPH_H_
#define MIS_GRAPH_H_

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include "node.h"

struct Edge
{
    long start_;        // edge start id
    long end_;          // edge end id
    double weight_;     // edge weight

    Edge(long s, long e, double w):start_(s), end_(e), weight_(w)
    {}

    void printEdge() const
    {
        std::cout << " (" << start_ << ", " << end_ << ", " << weight_ << ") ";
    }
};

class Graph
{
private:
    long nodeNum_;                  // node num
    long edgeNum_;                  // edge num
    std::vector<Node> nodes_;       // node set
    std::vector<Edge> edges_;       // edge set
private:
    static int X_MAX;
    static int Y_MAX;
public:
    // constructor
    Graph(long n, int radius);

    // distance from nodes_[i] to nodes_[j]
    double distance(long i, long j) const;

    // add edge from nodes_[i] to nodes_[j]
    void addEdge(long start, long end, double w);

    void printGraph() const;

public:
    // set plot screen weight and height
    static void setWidthHeight(int w, int h);
};


#endif // MIS_GRAPH_H_