#include "brick.h"
#include<iostream>

brick::brick(int x, int y)
{
    image.load(":/brick2.png");
    rect = image.rect();
    rect.translate(x, y);
    destoryed = false;
}

brick::~brick()
{
    //std::cout<<"A Brick is deleted !"<<std::endl;
}

void brick::resetStatus()
{
    rect.moveTo(0, 0);
}

void brick::setDestoryed(bool dest)
{
    destoryed = dest;
}

void brick::setRect(QRect rectp)
{
    rect = rectp;
}

QImage& brick::getImage()
{
    return image;
}

QRect brick::getRect()
{
    return rect;
}

bool brick::isDestoryed()
{
    return destoryed;
}
