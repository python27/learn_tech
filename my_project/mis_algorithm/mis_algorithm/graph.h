/*****************************************************************************
** FileName:    graph.h
** RelateFile:  graph.cpp test_graph.cpp
** Version:     1.0
** Author:      Xinfeng Li
** Date:        2013/10/30
**
** Description: This file is used to declare the Graph class, which mainly used 
**              by the Graph class.
**              
** Copyright (C), 2013, Xinfeng Li, Zhejiang University             
**
*****************************************************************************/
#ifndef MIS_GRAPH_H_
#define MIS_GRAPH_H_

#include <QtGui>        // Qt dependency
#include <QtCore>       // Qt dependency
#include <QPainter>     // Qt dependency

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

    // constructor
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
    static int X_MAX;               // ploting screen max width
    static int Y_MAX;               // ploting screen max height
public:
    /*********************************************************** 
     * constructor
     * 
     * Input:
     * n - number of nodes
     * radius - boarding radius of every node
     *
     * Output:
     * A whole graph
     ***********************************************************/
    Graph(long n, int radius);

    /************************************************************ 
     * return distance from node i to node j
     ***********************************************************/
    double distance(long i, long j) const;

    /*************************************************************
     * Add edge to the graph
     * Input:
     * start - edge start point
     * end - edge end point
     * weight - edge weight, in this example it represent distance
     *          from start to end
     ************************************************************/
    void addEdge(long start, long end, double w);

    void printGraph() const;

    /*************************************************************
     * paint the current graph
     *************************************************************/
    void paintGraph(QPainter &painter) const;

public:
    /************************************************************* 
     * reset the plot zone height and width
     *************************************************************/
    static void setWidthHeight(int w, int h);
};


#endif // MIS_GRAPH_H_
