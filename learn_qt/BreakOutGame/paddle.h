#ifndef PADDLE_H
#define PADDLE_H

#include<QRect>
#include<QImage>

class paddle
{
public:
    paddle();
    ~paddle();

public:
    void resetStatus();
    void moveLeft(int left);
    void moveRight(int right);

    QRect getRect();
    QImage& getImage();

private:
    QRect rect;
    QImage image;
};

#endif // PADDLE_H
