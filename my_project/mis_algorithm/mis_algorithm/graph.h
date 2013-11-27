/*****************************************************************************
** FileName:    graph.h
** RelateFile:  graph.cpp test_graph.cpp
** Version:     1.0
** Author:      Xinfeng Li
** Date:        2013/10/30
** Update:      2013/11/12
**
** Log
** --------------------------------------------------------------------------
** Time         Author          revise
** --------------------------------------------------------------------------
** 2013/10/30   Xinfeng Li      created
** 2013/11/12   Xinfeng Li      add MCDS algorithm
** 2013/11/27   Xinfeng Li      add keyLinks_ attribution to the graph
**                              also addKeyLinks member functions
** --------------------------------------------------------------------------
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

    bool operator<(const Edge &other) const
    {
        if (start_ != other.start_)
        {
            return start_ < other.start_;
        }
        else
        {
            return end_ < other.end_;
        }
    }
};


class Graph
{
private:
    long nodeNum_;                  // node num
    long edgeNum_;                  // edge num
    std::vector<Node> nodes_;       // node set
    std::vector<Edge> edges_;       // edge set
    std::set<Edge> keyLinks_;       // key edges of the graph
private:
    static int X_MAX;               // ploting screen max width
    static int Y_MAX;               // ploting screen max height
public:

    Graph();

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


    /************************************************************
     * Add the edge to the key links of the graph
     *
     * version1:
     * Input:
     * start -- start point of the edge to be added
     * end -- end point of the edge to be added
     * w -- the weight of the edge to be added
     *
     * version2:
     * Input:
     * e - the edge to be added
     *
     * update by Xinfeng Li
     * Date: 2013/11/27
     ************************************************************/
    void addKeyLink(long start, long end, double w);
    void addKeyLink(const Edge& e);

    void printGraph() const;

    /*************************************************************
     * paint the current graph
     *************************************************************/
    void paintGraph(QPainter &painter) const;

public:// these member function used by MIS Algorithm
    /*************************************************************
     * return if all nodes' states have been changed
     *************************************************************/
    bool allNodeStateChanged() const;

    /********************************************************************
     * boardcast Message from srcId to all its neighbours
     ********************************************************************/
    void broadcastMessage(long srcId, NodeState s);

    /*********************************************************************
     * MIS Algorithm: find all critical nodes in the network
     *
     * Main Idea:
     * 1. If there is no neighbors whose ID is smaller than current node
     *    set it to the DOMINATOR node, then boardcast DOMINATORMessage
     * 2. if node is CANDIDATE && receive DOMINATORMessage, then set current
     *    state to DOMINATEE, then boardcast DOMINATEEMessage
     * 3. if node is CANDIDATE && receive DOMINATEEMessage, if src node id
     *    is smaller than current node, then nLower--, if nLower == 0, set
     *    current state to DOMINATOR, boardcast DOMINATORMessage
     *********************************************************************/
    void MISAlgorithm();

    /**********************************************************************
     * MCDSAlgorithm: find all the CONNECTOR node in the graph
     *
     * Main Idea:
     * 1. all the DOMINATOR nodes broadcast Request_DOMI message to its
     *    neighbours
     * 2. if the neighbour is DOMINATEE node, then the neighbour add its
     *    node index to the message path, then continue broadcast
     *    Request_DOMI messge to its neighbour, until the message has been
     *    boardcast at most 3 times
     * 3. if the neighbour is DOMINATOR node, then it generate a Reply_DOMI
     *    message to its neighbours
     * 4. if the neighbours (step 3's) received Reply_DOMI, examine whether
     *    its node index in the message path route, if yes, reset the node
     *    set to CONNECTOR state. if no, do nothing. then broadcast the
     *    Reply_DOMI message.
     *
     **********************************************************************/
    void MCDSAlgorithm();

public:
    /************************************************************* 
     * reset the plot zone height and width
     *************************************************************/
    static void setWidthHeight(int w, int h);
};


#endif // MIS_GRAPH_H_
