/*****************************************************************************
** FileName:    message.h
** RelateFile:  graph.cpp
** Version:     1.0
** Author:      Xinfeng Li
** Date:        2013/11/12
**
** Description: This file is used to declare the Message class, which mainly used
**              by the MCDS algorithm, which is a submethod in graph class.
**
** Copyright (C), 2013, Xinfeng Li, Zhejiang University
**
*****************************************************************************/
#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <vector>

struct RequestMsg
{
    long msgSrc_;                   // source id which send this message
    std::vector<long> msgPath_;     // message path from source id, but not include source id
    int broadcastCnt_;              // the number of broadcast, in MCDS algorithm, it must
                                    // be no more than 3

    // constructor
    RequestMsg():msgSrc_(0), broadcastCnt_(1){}
    RequestMsg(long src, int cnt):msgSrc_(src), broadcastCnt_(cnt){}

    // append id to the message path
    inline void appendPath(long id)
    {
        msgPath_.push_back(id);
    }

    // print Message info
    void printMessage() const
    {
        std::cout << "### Message BEGIN ###"  << std::endl;
        std::cout << "source: < " << msgSrc_ << " >" << std::endl;
        std::cout << "path: < ";
        for (int i = 0; i < msgPath_.size(); ++i)
        {
            std::cout << msgPath_[i] << " ";
        }
        std::cout << ">" << std::endl;
        std::cout << "count: < " << broadcastCnt_ << " >" << std::endl;
        std::cout << "### Message  END  ###" << std::endl;
    }

};

#endif // MESSAGE_H
