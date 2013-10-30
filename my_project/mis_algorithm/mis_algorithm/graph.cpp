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
		double xx = std::rand() % X_MAX;
		double yy = std::rand() % Y_MAX;
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
	cout << "Edge Number: " << edgeNum_ << endl;
	cout << "Edges: " << "{ ";
	for (long i = 0; i < edgeNum_; ++i)
	{
		edges_[i].printEdge();
	} 
	cout << " }" << endl;
	cout << "****************Graph Info END****************" << endl;
}