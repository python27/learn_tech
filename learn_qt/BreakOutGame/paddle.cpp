#include "paddle.h"
#include<iostream>

paddle::paddle()
{
    image.load(":/paddle2.png");
    rect = image.rect();
    std::cout<<"the paddle width:"<<rect.width()<<std::endl;
    std::cout<<"the paddle height:"<<rect.height()<<std::endl;

    resetStatus();
}

paddle::~paddle()
{
    std::cout<<"paddle is deleted !"<<std::endl;
}

void paddle::resetStatus()
{
    rect.moveTo(200, 360);
}

void paddle::moveLeft(int left)
{
    if (rect.left() >=2)
    {
        rect.moveTo(left, rect.top());
    }
}

void paddle::moveRight(int right)
{
    if (rect.right() <= 298)
    {
        rect.moveTo(right, rect.top());
    }
}

QRect paddle::getRect()
{
    return rect;
}

QImage& paddle::getImage()
{
    return image;
}

