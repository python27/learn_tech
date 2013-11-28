/*****************************************************************************
** FileName:    graph.cpp
** RelateFile:  test_graph.cpp
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
** 2013/11/13   Xinfeng Li      finish editing MCDS algorithm
** 2013/11/14   Xinfeng Li      debug the MCDS algorithm, revise the paintGraph
**                              function to indicate the key path between DOMINATOR
**                              nodes and CONNECTOR
** 2013/11/27   Xinfeng Li      revise MCDS algorithm to calculate the key links in
**                              the graph
** 2013/11/28   Xinfeng Li      Add BFS algorithm to find the final key links from the
**                              possible key links with extra links
** --------------------------------------------------------------------------
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

#include <queue>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "node.h"
#include "graph.h"
#include "message.h"
using std::cout;
using std::endl;

int Graph::X_MAX = 400;
int Graph::Y_MAX = 400;

Graph::Graph(long n, int radius)
{
    keyLinks_.clear();
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

Graph::Graph()
{
    Node node1(0, 200, 300, 100);
    Node node2(1, 200, 200, 100);
    Node node3(2, 400, 300, 100);
    Node node4(3, 400, 200, 100);
    Node node5(4, 300, 300, 100);
    Node node6(5, 300, 200, 100);
    nodeNum_ = 6;
    nodes_.push_back(node1);
    nodes_.push_back(node2);
    nodes_.push_back(node3);
    nodes_.push_back(node4);
    nodes_.push_back(node5);
    nodes_.push_back(node6);
    addEdge(0, 1, 1);
    nodes_[0].addNeighbour(1);
    nodes_[1].addNeighbour(0);
    addEdge(1, 4, 1);
    nodes_[1].addNeighbour(4);
    nodes_[4].addNeighbour(1);
    addEdge(1, 5, 1);
    nodes_[1].addNeighbour(5);
    nodes_[5].addNeighbour(1);
    addEdge(2, 3, 1);
    nodes_[2].addNeighbour(3);
    nodes_[3].addNeighbour(2);
    addEdge(2, 4, 1);
    nodes_[2].addNeighbour(4);
    nodes_[4].addNeighbour(2);
    addEdge(3, 4, 1);
    nodes_[3].addNeighbour(4);
    nodes_[4].addNeighbour(3);
    addEdge(3, 5, 1);
    nodes_[3].addNeighbour(5);
    nodes_[5].addNeighbour(3);
    edgeNum_ = edges_.size();
}


double Graph::distance(long i, long j) const
{
	double dx = nodes_[i].position_.first - nodes_[j].position_.first;
	double dy = nodes_[i].position_.second - nodes_[j].position_.second;
	return std::sqrt(dx * dx + dy * dy);
}

void Graph::addKeyLink(long start, long end, double w)
{
    Edge e(start, end, w);
    keyLinks_.insert(e);
}


void Graph::addKeyLink(const Edge& e)
{
    keyLinks_.insert(e);
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
    // reset brush and pen, paint the edge
    painter.setBrush(Qt::black);
    painter.setPen(QColor(0,0,0));

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

#if 0
        // whether the two nodes are CONNECTOR or DOMINATOR
        if ( (nodes_[s].currentState_ == DOMINATOR || nodes_[s].currentState_ == CONNECTOR) &&
             (nodes_[e].currentState_ == DOMINATOR || nodes_[e].currentState_ == CONNECTOR) )
        {
            painter.setBrush(Qt::red);
            painter.setPen(QColor(255, 0, 0));
        }
        else
        {
            painter.setBrush(Qt::black);
            painter.setPen(QColor(0, 0, 0));
        }
#endif //


        painter.drawLine(nodes_[s].position_.first, nodes_[s].position_.second,
                         nodes_[e].position_.first, nodes_[e].position_.second);
    }

    // if the keylinks is not empty, paint the keylinks
    if (keyLinks_.empty())
    {
        return;
    }

    painter.setBrush(Qt::red);
    painter.setPen(QColor(255, 0, 0));
    for (auto it = keyLinks_.begin(); it != keyLinks_.end(); ++it)
    {
        long s = it->start_;
        long e = it->end_;

        painter.drawLine(nodes_[s].position_.first, nodes_[s].position_.second,
                         nodes_[e].position_.first, nodes_[e].position_.second);
    }
}

bool Graph::allNodeStateChanged() const
{
    for (long i = 0; i < nodeNum_; ++i)
    {
        if (nodes_[i].currentState_ == CANDIDATE)
        {
            return false;
        }
    }
    return true;
}

void Graph::broadcastMessage(long srcId, NodeState s)
{
    for (std::set<long>::iterator it = nodes_[srcId].neighbours_.begin();
         it != nodes_[srcId].neighbours_.end(); ++it)
    {
        // if srcId's neighbour hasn't received any message, then received
        // the message, else just ignore the message send to it.
        // In other words, one node just follow the first node who gives it
        // message.
        if (nodes_[*it].receivedState_ == CANDIDATE)
        {
            nodes_[*it].setReceivedState(s);
        }
        //std::cout << srcId << " Neighbours: " << *it << std::endl;
    }
}

void Graph::MISAlgorithm()
{
    // init nLower array
    std::vector<long> nLower(nodeNum_);
    for (long i = 0; i < nodeNum_; ++i)
    {
        nLower[i] = nodes_[i].getNLower();
    }

    while (!allNodeStateChanged())
    {
        // step 1: find all Dominator node and boardcast Message
        for (long i = 0; i < nodeNum_; ++i)
        {
            if (nodes_[i].currentState_ == CANDIDATE && nLower[i] == 0)
            {

                nodes_[i].currentState_ = DOMINATOR;
                broadcastMessage(i, DOMINATOR);
                //std::cout << "Dominator: " << i << std::endl;
            }
        }

        // step 2: find all CANDIDATE node which received DOMINATOR Message
        //         change current state and boardcast
        for (long i = 0; i < nodeNum_; ++i)
        {
            if (nodes_[i].currentState_ == CANDIDATE &&
                nodes_[i].receivedState_ == DOMINATOR)
            {
                nodes_[i].currentState_ = DOMINATEE;
                broadcastMessage(i, DOMINATEE);
                //std::cout << "Dominatee: " << i << std::endl;
            }
        }

        // step 3: change nlower, find new DOMINATOR node
        for (long i = 0; i < nodeNum_; ++i)
        {
            // calculate current nLower;
            if (nodes_[i].currentState_ == CANDIDATE &&
                nodes_[i].receivedState_ == DOMINATEE)
            {
                long lower = 0;
                for (std::set<long>::iterator it = nodes_[i].neighbours_.begin();
                                              it != nodes_[i].neighbours_.end(); ++it)
                {
                    if(*it < i && nodes_[*it].currentState_ == CANDIDATE)
                    {
                        lower++;
                    }
                }
                nLower[i] = lower;

                //if (nLower[i] == 0)
                //{
                //    std::cout << "New maybe Dominator: " << i << std::endl;
                //}
            }
        }
    }
}

void Graph::MCDSAlgorithm()
{
    // store all the possible key links in the graph
    std::set<Edge> curKeyLinks;

    // step 1. DOMINATOR nodes broadcast Request_DOMI message
    for (long i = 0; i < nodeNum_; ++i)
    {
        if (nodes_[i].currentState_ == DOMINATOR)
        {
            // created Request_DOMI message
            nodes_[i].pRequestMsg_ = new RequestMsg(i, 1);

            // boardcast to its every neighbour
            for (std::set<long>::iterator it = nodes_[i].neighbours_.begin();
                                          it != nodes_[i].neighbours_.end();  ++it)
            {
                if (nodes_[*it].currentState_ == DOMINATEE)
                {
                    // node hasn't received any requestMsg && message hasn't
                    // been broadcasted to this node
                    if ( nodes_[*it].receivedRequestMsg_ == false &&
                         nodes_[*it].pRequestMsg_ == NULL &&
                         !(nodes_[i].pRequestMsg_->containNode(*it)) )
                    {
                        nodes_[*it].receivedRequestMsg_ = true;
                        nodes_[*it].pRequestMsg_ = new RequestMsg(*(nodes_[i].pRequestMsg_));
                        (nodes_[*it].pRequestMsg_)->appendPath(*it);
                    }
                }
                else if (nodes_[*it].currentState_ == DOMINATOR)
                {
                    // node hasn't generated any replyMsg &&
                    // the index of the node is not equal to message source node id
                    if ( nodes_[*it].receivedRequestMsg_ == false &&
                         nodes_[*it].pRequestMsg_ == NULL &&
                         nodes_[*it].hasReplyMsg_ == false &&
                         *it != (nodes_[i].pRequestMsg_)->msgSrc_)
                    {
                        nodes_[*it].receivedRequestMsg_ = true;
                        nodes_[*it].hasReplyMsg_ = true;
                        nodes_[*it].pReplyMsg_ = new ReplyMsg( *(nodes_[i].pRequestMsg_) );
#if 1
                        // get the all the nodes on the key links based on the Reply Message
                        std::vector<long> tempAllNodes( (nodes_[*it].pReplyMsg_->msgPath_).begin(),
                                                        (nodes_[*it].pReplyMsg_->msgPath_).end()   );
                        tempAllNodes.insert(tempAllNodes.begin(), *it);
                        tempAllNodes.push_back(nodes_[*it].pReplyMsg_->msgSrc_);

                        // add all the key links linearly by the key nodes one by one
                        // into the keyLinks_ data member of the graph
                        for (int i = 0; i < tempAllNodes.size() - 1; ++i)
                        {
                            Edge tmpEdge(tempAllNodes[i], tempAllNodes[i+1], 0);
                            curKeyLinks.insert(tmpEdge);
                            //addKeyLink(tempAllNodes[i], tempAllNodes[i+1], 0);
                        }
#endif //0

                    }

                }
            }

            // free Request_DOMI message
            delete nodes_[i].pRequestMsg_;
            nodes_[i].pRequestMsg_ = NULL;
        }
    }

    // step 2. All the nodes which received Request_DOMI message
    //         broadcast Request_DOMI message to its neighbours
    for (long i = 0; i < nodeNum_; ++i)
    {
        // all the DOMINATEE nodes broadcast message
        // DOMINATOR nodes just wait to received message and
        // generate ReplyMsg, no need to broadcast message
        if (nodes_[i].currentState_ == DOMINATEE)
        {
            if (nodes_[i].pRequestMsg_ != NULL)
            {
                // boardcast to its every neighbour
                for (std::set<long>::iterator it = nodes_[i].neighbours_.begin();
                                              it != nodes_[i].neighbours_.end();  ++it)
                {
                    if (nodes_[*it].currentState_ == DOMINATEE)
                    {
                        // node hasn't received any requestMsg && message hasn't
                        // been broadcasted to this node
                        if ( nodes_[*it].pRequestMsg_ == NULL &&
                             !(nodes_[i].pRequestMsg_->containNode(*it)) )
                        {
                            nodes_[*it].receivedRequestMsg_ = true;
                            nodes_[*it].pRequestMsg_ = new RequestMsg(*(nodes_[i].pRequestMsg_));
                            (nodes_[*it].pRequestMsg_)->appendPath(*it);
                        }
                        // although neighbour has received requestMsg, but the msgSrc
                        // it larger than the current message source node
                        else if ( nodes_[*it].pRequestMsg_ != NULL &&
                                  !(nodes_[i].pRequestMsg_->containNode(*it)) &&
                                  (nodes_[*it].pRequestMsg_)->msgSrc_ > (nodes_[i].pRequestMsg_)->msgSrc_ )
                        {
                            nodes_[*it].receivedRequestMsg_ = true;
                            delete nodes_[*it].pRequestMsg_;
                            nodes_[*it].pRequestMsg_ = NULL;
                            nodes_[*it].pRequestMsg_ = new RequestMsg(*(nodes_[i].pRequestMsg_));
                            nodes_[*it].pRequestMsg_->appendPath(*it);
                        }
                    }
                    else if (nodes_[*it].currentState_ == DOMINATOR)
                    {
                        // node hasn't generated any replyMsg &&
                        // the index of the node is not equal to message source node id
                        if ( nodes_[*it].pReplyMsg_ == NULL &&
                             !(nodes_[i].pRequestMsg_->containNode(*it)) )
                        {
                            nodes_[*it].receivedRequestMsg_ = true;
                            nodes_[*it].hasReplyMsg_ = true;
                            nodes_[*it].pReplyMsg_ = new ReplyMsg( *(nodes_[i].pRequestMsg_) );

#if 1
                            // get the all the nodes on the key links based on the Reply Message
                            std::vector<long> tempAllNodes( (nodes_[*it].pReplyMsg_->msgPath_).begin(),
                                                            (nodes_[*it].pReplyMsg_->msgPath_).end() );
                            tempAllNodes.insert(tempAllNodes.begin(), *it);
                            tempAllNodes.push_back(nodes_[*it].pReplyMsg_->msgSrc_);

                            // add all the key links linearly by the key nodes one by one
                            // into the keyLinks_ data member of the graph
                            for (int i = 0; i < tempAllNodes.size() - 1; ++i)
                            {
                                Edge tmpEdge(tempAllNodes[i], tempAllNodes[i+1], 0);
                                curKeyLinks.insert(tmpEdge);
                                //addKeyLink(tempAllNodes[i], tempAllNodes[i+1], 0);
                            }
#endif //0
                        }
                        // DOMINATOR nodes which has generated ReplyMessage, but the message
                        // source node index is large than current message node index, update
                        else if (nodes_[*it].pReplyMsg_ != NULL &&
                                 !(nodes_[i].pRequestMsg_->containNode(*it)) &&
                                 nodes_[*it].pReplyMsg_->msgSrc_ > nodes_[i].pRequestMsg_->msgSrc_)
                        {
                            delete nodes_[*it].pReplyMsg_;
                            nodes_[*it].pReplyMsg_ = NULL;
                            nodes_[*it].pReplyMsg_ = new ReplyMsg( *(nodes_[i].pRequestMsg_) );
                            nodes_[*it].hasReplyMsg_ = true;
#if 1
                            // get the all the nodes on the key links based on the Reply Message
                            std::vector<long> tempAllNodes( (nodes_[*it].pReplyMsg_->msgPath_).begin(),
                                                            (nodes_[*it].pReplyMsg_->msgPath_).end() );
                            tempAllNodes.insert(tempAllNodes.begin(), *it);
                            tempAllNodes.push_back(nodes_[*it].pReplyMsg_->msgSrc_);

                            // add all the key links linearly by the key nodes one by one
                            // into the keyLinks_ data member of the graph
                            for (int i = 0; i < tempAllNodes.size() - 1; ++i)
                            {
                                Edge tmpEdge(tempAllNodes[i], tempAllNodes[i+1], 0);
                                curKeyLinks.insert(tmpEdge);
                                //addKeyLink(tempAllNodes[i], tempAllNodes[i+1], 0);
                            }
#endif //0
                        }

                    }
                }
                delete nodes_[i].pRequestMsg_;
                nodes_[i].pRequestMsg_ = NULL;
            }
        }
    }

    // step 3. same with step 2
    for (long i = 0; i < nodeNum_; ++i)
    {
        // all the DOMINATEE nodes broadcast message
        // DOMINATOR nodes just wait to received message and
        // generate ReplyMsg, no need to broadcast message
        if (nodes_[i].currentState_ == DOMINATEE)
        {
            if (nodes_[i].pRequestMsg_ != NULL)
            {
                // boardcast to its every neighbour
                for (std::set<long>::iterator it = nodes_[i].neighbours_.begin();
                                              it != nodes_[i].neighbours_.end();  ++it)
                {
                    if (nodes_[*it].currentState_ == DOMINATEE)
                    {
                        // node hasn't received any requestMsg && message hasn't
                        // been broadcasted to this node
                        if ( nodes_[*it].pRequestMsg_ == NULL &&
                             !(nodes_[i].pRequestMsg_->containNode(*it)) )
                        {
                            nodes_[*it].receivedRequestMsg_ = true;
                            nodes_[*it].pRequestMsg_ = new RequestMsg(*(nodes_[i].pRequestMsg_));
                            (nodes_[*it].pRequestMsg_)->appendPath(*it);
                        }
                        // although neighbour has received requestMsg, but the msgSrc
                        // it larger than the current message source node
                        else if ( nodes_[*it].pRequestMsg_ != NULL &&
                                  !(nodes_[i].pRequestMsg_->containNode(*it)) &&
                                  (nodes_[*it].pRequestMsg_)->msgSrc_ > (nodes_[i].pRequestMsg_)->msgSrc_)
                        {
                            nodes_[*it].receivedRequestMsg_ = true;
                            delete nodes_[*it].pRequestMsg_;
                            nodes_[*it].pRequestMsg_ = NULL;
                            nodes_[*it].pRequestMsg_ = new RequestMsg(*(nodes_[i].pRequestMsg_));
                            nodes_[*it].pRequestMsg_->appendPath(*it);
                        }
                    }
                    else if (nodes_[*it].currentState_ == DOMINATOR)
                    {
                        // node hasn't generated any replyMsg &&
                        // the index of the node is not equal to message source node id
                        if ( nodes_[*it].pReplyMsg_ == NULL &&
                             !(nodes_[i].pRequestMsg_->containNode(*it)) )
                        {
                            nodes_[*it].receivedRequestMsg_ = true;
                            nodes_[*it].hasReplyMsg_ = true;
                            nodes_[*it].pReplyMsg_ = new ReplyMsg( *(nodes_[i].pRequestMsg_) );
#if 1
                            // get the all the nodes on the key links based on the Reply Message
                            std::vector<long> tempAllNodes( (nodes_[*it].pReplyMsg_->msgPath_).begin(),
                                                            (nodes_[*it].pReplyMsg_->msgPath_).end() );
                            tempAllNodes.insert(tempAllNodes.begin(), *it);
                            tempAllNodes.push_back(nodes_[*it].pReplyMsg_->msgSrc_);

                            // add all the key links linearly by the key nodes one by one
                            // into the keyLinks_ data member of the graph
                            for (int i = 0; i < tempAllNodes.size() - 1; ++i)
                            {
                                Edge tmpEdge(tempAllNodes[i], tempAllNodes[i+1], 0);
                                curKeyLinks.insert(tmpEdge);
                                //addKeyLink(tempAllNodes[i], tempAllNodes[i+1], 0);
                            }
#endif //0
                        }
                        // DOMINATOR nodes which has generated ReplyMessage, but the message
                        // source node index is large than current message node index, update
                        else if (nodes_[*it].pReplyMsg_ != NULL &&
                                 !(nodes_[i].pRequestMsg_->containNode(*it)) &&
                                 nodes_[*it].pReplyMsg_->msgSrc_ > nodes_[i].pRequestMsg_->msgSrc_)
                        {
                            delete nodes_[*it].pReplyMsg_;
                            nodes_[*it].pReplyMsg_ = NULL;
                            nodes_[*it].pReplyMsg_ = new ReplyMsg( *(nodes_[i].pRequestMsg_) );
                            nodes_[*it].hasReplyMsg_ = true;

#if 1
                            // get the all the nodes on the key links based on the Reply Message
                            std::vector<long> tempAllNodes( (nodes_[*it].pReplyMsg_->msgPath_).begin(),
                                                            (nodes_[*it].pReplyMsg_->msgPath_).end() );
                            tempAllNodes.insert(tempAllNodes.begin(), *it);
                            tempAllNodes.push_back(nodes_[*it].pReplyMsg_->msgSrc_);

                            // add all the key links linearly by the key nodes one by one
                            // into the keyLinks_ data member of the graph
                            for (int i = 0; i < tempAllNodes.size() - 1; ++i)
                            {
                                Edge tmpEdge(tempAllNodes[i], tempAllNodes[i+1], 0);
                                curKeyLinks.insert(tmpEdge);
                                //addKeyLink(tempAllNodes[i], tempAllNodes[i+1], 0);
                            }

#endif //0
                        }

                    }
                }
                delete nodes_[i].pRequestMsg_;
                nodes_[i].pRequestMsg_ = NULL;
            }
        }
    }

    // find all nodes in the ReplyMessage held by the DOMINATOR nodes
    // if they are DONIMATEE state, then reset them to be CONNECTOR
    for (long i = 0; i < nodeNum_; ++i)
    {
        if (nodes_[i].currentState_ == DOMINATOR && nodes_[i].pReplyMsg_ != NULL)
        {
            std::vector<long> pathNodes(nodes_[i].pReplyMsg_->msgPath_);
            for (size_t j = 0; j < pathNodes.size(); ++j)
            {
                long neighbour = pathNodes[j];
                if (nodes_[neighbour].currentState_ == DOMINATEE)
                {
                    nodes_[neighbour].currentState_ = CONNECTOR;
                }
            }
        }
    }


    /*********************************************************************
     * BFS the graph constructed by the current key Links to
     * remove the extra links, thus get the final minimal connected
     * dominator set
     *
     * Xinfeng Li
     * 2013/11/28
     **/

    // store all the key nodes which ocuur in the current possible key links
    std::set<long> curKeyNodes;

    // difine the current adjancency matrix of the graph
    // init and assign value
    std::vector<std::vector<int> > matrix(nodeNum_, std::vector<int>(nodeNum_, 0));
    for (std::set<Edge>::iterator it = curKeyLinks.begin(); it != curKeyLinks.end(); ++it)
    {
        matrix[it->start_][it->end_] = 1;
        matrix[it->end_][it->start_] = 1;

        curKeyNodes.insert(it->start_);
        curKeyNodes.insert(it->end_);
    }

    // bfs algorithm
    // Note: the graph may have more than one connected component
    //       So add the curKeyNodes set to record which nodes that
    //       that haven't been visited by the bfs algorithm
    while (!curKeyNodes.empty())
    {
        long bfs_firstNode = *(curKeyNodes.begin());

        std::vector<bool> bfs_visited(nodeNum_, false);
        std::queue<long> q;

        bfs_visited[bfs_firstNode];
        q.push(bfs_firstNode);

        curKeyNodes.erase(bfs_firstNode);   // has been visited, then delete
        while (!q.empty())
        {
            long tmpNode = q.front();
            q.pop();
            for (long j = 0; j < nodeNum_; ++j)
            {
                if (matrix[tmpNode][j] != 0 && bfs_visited[j] == false)
                {
                    bfs_visited[j] = true;
                    addKeyLink(tmpNode, j, 0);
                    curKeyNodes.erase(j);   // has been visited, then delete
                    q.push(j);
                }
            }
        }
    }


#if 0
    // find all the key links in the graph
    // add them to the keyLinks_ data member
    for (long i = 0; i < nodeNum_; ++i)
    {
        if (nodes_[i].currentState_ == DOMINATOR && nodes_[i].pReplyMsg_ != NULL)
        {
            // get the all the nodes on the key links based on the Reply Message
            std::vector<long> tempAllNodes( (nodes_[i].pReplyMsg_->msgPath_).begin(),
                                            (nodes_[i].pReplyMsg_->msgPath_).end() );
            tempAllNodes.insert(tempAllNodes.begin(), i);
            tempAllNodes.push_back(nodes_[i].pReplyMsg_->msgSrc_);

            // add all the key links linearly by the key nodes one by one
            // into the keyLinks_ data member of the graph
            for (int k = 0; k < tempAllNodes.size() - 1; ++k)
            {
                addKeyLink(tempAllNodes[k], tempAllNodes[k+1], 0);
            }

        }
    }
#endif // 0

    return;
}
