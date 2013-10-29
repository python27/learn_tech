/*****************************************************************************
** FileName:    Node.h
** RelateFile:  test_node.cpp
** Version:     1.0
** Author:      Xinfeng Li
** Date:        2013/10/29
**
** Description: This file is used to declare the Node class, which mainly used 
**              by the Graph class.
**              
** Copyright (C), 2013, Xinfeng Li, Zhejiang University             
**
*****************************************************************************/
#ifndef MIS_NODE_H
#define MIS_NODE_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

/*********************************************************
 * Node status definition
 ********************************************************/
enum NodeState{CANDIDATE, DOMINATOR, DOMINATEE, CONNECTOR};


/*****************************************************************************
 * class Node declare
 ****************************************************************************/
struct Node
{
    long id_;                                   // identifier
    std::pair<double, double> position_;        // node position in coordinate
    int boardRadius_;                           // message boarding range
    std::set<long> neighbours_;                 // neighbours of the current node
    NodeState currentState_;                    // current node state
    NodeState receivedState_;                   // receive message state

public:
    // constructor
    Node():id_(0), 
           position_(0.0, 0.0), 
           boardRadius_(0),
           currentState_(CANDIDATE),
           receivedState_(CANDIDATE)
    {}
    
    // constructor
    Node(long id, double xx, double yy, int radius): id_(id),
                                                     position_(xx, yy),
                                                     boardRadius_(radius),
                                                     currentState_(CANDIDATE),
                                                     receivedState_(CANDIDATE)
    {}


    // set node to position (x, y)
    inline void setPosition(double x, double y)
    {
        position_.first = x;
        position_.second = y;    
    }

    // add new neighbour
    inline void addNeighbour(long id)
    {
        if (id == id_)
        {
            return;
        }
        else
        {
            neighbours_.insert(id);
        }
    }

    // set new current state
    inline void setCurrentState(NodeState state)
    {
        currentState_ = state;
    }

    // set received state
    inline void setReceivedState(NodeState state)
    {
        receivedState_ = state;
    }

    // get the number of neighbours whose id is smaller than it 
    inline int getNLower() const
    {
        long cnt = 0;
        for (set<long>::iterator it = neighbours_.begin(); 
                                 it != neighbours_.end(); ++it)
        {
            if (*it < id_)
            {
                cnt++;
            }
        }
        return cnt;
    }

    void printNode() const
    {
        std::cout << "**********BEGIN NODE INFO**********" << std::endl;
        std::cout << "ID: \t\t\t" << id_ << std::endl;
        std::cout << "Postion: \t\t" << "( " 
                  << position_.first << ", " << position_.second << " )" 
                  << std:: endl;

        std::cout << "Radius: \t\t" << boardRadius_ << std::endl; 

        std::cout << "Neighbors: \t\t" << "{";
        for (set<long>::iterator it = neighbours_.begin(); it != neighbours_.end(); ++it)
        {
            std::cout << " " << *it;
        }
        std::cout << " }" << std::endl;

        std::cout << "Current State: \t\t" << currentState_ << std::endl;
        std::cout << "Received State: \t" << receivedState_ << std::endl;
        std::cout << "nLower: \t\t" << getNLower() << std::endl;
        std::cout << "***********END NODE INFO***********" << std::endl;

    }
};


#endif // MIS_NODE_H
