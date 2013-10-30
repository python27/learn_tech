/*****************************************************************************
** FileName:    graph.cpp
** RelateFile:  test_graph.cpp
** Version:     1.0
** Author:      Xinfeng Li
** Date:        2013/10/30
**
** Description: This file is used to declare the Graph class, which mainly used 
**              by the Graph class.
** Note:		All the function description has been commented in the graph.h
**              header file, please refer to it.
**              
** Copyright (C), 2013, Xinfeng Li, Zhejiang University             
**
*****************************************************************************/
#include <QtGui>
#include <QtCore>
#include <QPainter>

#include <cstdlib>
#include <ctime>
#include <cmath>
#include "node.h"
#include "graph.h"
using std::cout;
using std::endl;

int Graph::X_MAX = 400;
int Graph::Y_MAX = 400;

Graph::Graph(long n, int radius)
{
	nodeNum_ = n;

	// create all the nodes
	std::srand(time(NULL));
	for (long i = 0; i < nodeNum_; ++i)
	{
		// create the single node
        double xx = std::rand() % (X_MAX - 100) + 50;
        double yy = std::rand() % (Y_MAX - 100) + 50;
		Node tmp(i, xx, yy, radius);

		nodes_.push_back(tmp);
	}

	// create all the edges
	// caculate the distance between any two nodes, if
	// the distance is no greater than RADIUS, then they
	// are neighbours, add a edge between them
	for (long i = 0; i < nodeNum_; ++i)
	{
		for(long j = i + 1; j < nodeNum_; ++j)
		{
			double d = distance(i, j);
			if (d <= radius)
			{
				nodes_[i].addNeighbour(j);
				nodes_[j].addNeighbour(i);
				addEdge(i, j, d);
                //addEdge(j, i, d);
			}
		}
	}

	edgeNum_ = edges_.size();
}



double Graph::distance(long i, long j) const
{
	double dx = nodes_[i].position_.first - nodes_[j].position_.first;
	double dy = nodes_[i].position_.second - nodes_[j].position_.second;
	return std::sqrt(dx * dx + dy * dy);
}

void Graph::addEdge(long start, long end, double w)
{
	Edge tmp(start, end, w);
	edges_.push_back(tmp);
	edgeNum_++;
}

void Graph::setWidthHeight(int w, int h)
{
	X_MAX = w;
	Y_MAX = h;
}


void Graph::printGraph() const
{
	cout << "***************Graph Info BEGIN***************" << endl;
	cout << "Screen Size: (" << X_MAX << " * " << Y_MAX << ")" << endl;
	cout << "Board Radius:" << nodes_[0].boardRadius_ << endl;
	cout << "Node Number: " << nodeNum_ << endl;
    cout << "Nodes:" << endl;
    for (long i = 0; i < nodeNum_; ++i)
    {
        nodes_[i].printNode();
    }
	cout << "Edge Number: " << edgeNum_ << endl;
	cout << "Edges: " << "{ ";
	for (long i = 0; i < edgeNum_; ++i)
	{
		edges_[i].printEdge();
	} 
	cout << " }" << endl;
	cout << "****************Graph Info END****************" << endl;
}

void Graph::paintGraph(QPainter &painter) const
{
    // paint all the nodes based on their state
    for (long i = 0; i < nodeNum_; ++i)
    {
        switch(nodes_[i].currentState_)
        {
            case CANDIDATE: painter.setBrush(Qt::black);
                            painter.setPen(QColor(0,0,0));
                            break;
            case DOMINATOR: painter.setBrush(Qt::red);
                            painter.setPen(QColor(255, 0, 0));
                            break;
            case DOMINATEE: painter.setBrush(Qt::green);
                            painter.setPen(QColor(0, 255, 0));
                            break;
            case CONNECTOR: painter.setBrush(Qt::blue);
                            painter.setPen(QColor(0, 0, 255));
                            break;
        }

        painter.drawEllipse(nodes_[i].position_.first, nodes_[i].position_.second, 5, 5);
    }

    // reset brush and pen, paint the edge
    painter.setBrush(Qt::black);
    painter.setPen(QColor(0,0,0));
    for(long i = 0; i < edgeNum_; ++i)
    {
        long s = edges_[i].start_;
        long e = edges_[i].end_;
        painter.drawLine(nodes_[s].position_.first, nodes_[s].position_.second,
                         nodes_[e].position_.second, nodes_[e].position_.second);
    }
}
