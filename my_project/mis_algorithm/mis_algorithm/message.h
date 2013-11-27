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
#include <set>
#include <algorithm>

struct RequestMsg
{
    long msgSrc_;                   // source id which send this message
    std::vector<long> msgPath_;     // message path from source id, but not include source id
    int broadcastCnt_;              // the number of broadcast, in MCDS algorithm, it must
                                    // be no more than 3

    // constructor
    RequestMsg():msgSrc_(0), broadcastCnt_(1){}
    RequestMsg(long src, int cnt):msgSrc_(src), broadcastCnt_(cnt){}
    // copy constructor
    explicit RequestMsg(const RequestMsg& m):msgSrc_(m.msgSrc_),
                                    broadcastCnt_(m.broadcastCnt_ + 1),
                                    msgPath_(m.msgPath_)
    {}

    // append id to the message path
    inline void appendPath(long id)
    {
        msgPath_.push_back(id);
    }

    // whether the message pass by the id node
    bool containNode(long id) const
    {
        if (find(msgPath_.begin(), msgPath_.end(), id) != msgPath_.end() ||
            id == msgSrc_)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // print Message info
    void printMessage() const
    {
        std::cout << "### Message BEGIN ###"  << std::endl;
        std::cout << "source: < " << msgSrc_ << " >" << std::endl;
        std::cout << "path: < ";
        for (size_t i = 0; i < msgPath_.size(); ++i)
        {
            std::cout << msgPath_[i] << " ";
        }
        std::cout << ">" << std::endl;
        std::cout << "count: < " << broadcastCnt_ << " >" << std::endl;
        std::cout << "### Message  END  ###" << std::endl;
    }

};

struct ReplyMsg
{
    long msgSrc_;
    std::vector<long> msgPath_;
    int broadcastCnt_;

    // constructor
    ReplyMsg():msgSrc_(0), broadcastCnt_(1){}

    // construct reply message from request message
    explicit ReplyMsg(const RequestMsg& m)
    {
        msgSrc_ = m.msgSrc_;
        for (int i = m.msgPath_.size() - 1; i >= 0; --i)
        {
            msgPath_.push_back((m.msgPath_)[i]);
        }
        broadcastCnt_ = 1;
    }

};

#endif // MESSAGE_H
