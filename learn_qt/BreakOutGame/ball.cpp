#include "ball.h"
#include<iostream>

ball::ball()
{
    image.load(":/ball2.png");
    rect = image.rect();
    xdir = 1;
    ydir = -1;
    std::cout<<"the ball width:"<<rect.width()<<std::endl;
    std::cout<<"the ball height:"<<rect.height()<<std::endl;
    resetStatus();
}

ball::~ball()
{
    std::cout<<"the ball is deleted !"<<std::endl;
}

void ball::resetStatus()
{
    rect.moveTo(230, 355);
}

void ball::moveLeft(int left)
{
    rect.moveLeft(left);
}

void ball::moveRight(int right)
{
    rect.moveRight(right);
}

void ball::moveTop(int top)
{
    rect.moveTop(top);
}

void ball::moveBottom(int bottom)
{
    rect.moveBottom(bottom);
}

void ball::autoMove()
{
    rect.translate(xdir, ydir);

    if (rect.left() == 0)
    {
        xdir = 1;
    }
    if (rect.right() == 300)
    {
        xdir = -1;
    }
    if (rect.top() == 0)
    {
        ydir = 1;
    }
}

QImage& ball::getImage()
{
    return image;
}

QRect ball::getRect()
{
    return rect;
}

int ball::getXdir()
{
    return xdir;
}

int ball::getYdir()
{
    return ydir;
}

void ball::setXdir(int dir)
{
    xdir = dir;
}

void ball::setYdir(int dir)
{
    ydir = dir;
}
