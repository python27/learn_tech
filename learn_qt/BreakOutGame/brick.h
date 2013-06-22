#ifndef BRICK_H
#define BRICK_H

#include<QImage>
#include<QRect>

class brick
{
public:
    brick(int x, int y);
    ~brick();

public:
    void resetStatus();
    void setDestoryed(bool destory);
    void setRect(QRect rectp);
    QImage& getImage();
    QRect getRect();
    bool isDestoryed();

private:
    QImage image;
    QRect rect;
    bool destoryed;
    int position;
};

#endif // BRICK_H
