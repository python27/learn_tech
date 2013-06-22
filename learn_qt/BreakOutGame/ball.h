#ifndef BALL_H
#define BALL_H

#include<QImage>
#include<QRect>

class ball
{
public:
    ball();
    ~ball();

public:
    void resetStatus();
    void moveLeft(int left);
    void moveRight(int right);
    void moveTop(int top);
    void moveBottom(int bottom);
    void autoMove();
    QImage& getImage();
    QRect getRect();
    int getXdir();
    int getYdir();
    void setXdir(int dir);
    void setYdir(int dir);

private:
    QImage image;
    QRect rect;
    int speed;
    int angle;
    int xdir;
    int ydir;
    bool stuck;
};

#endif // BALL_H
