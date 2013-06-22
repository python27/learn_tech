#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <QWidget>
#include <QKeyEvent>
#include "brick.h"
#include "ball.h"
#include "paddle.h"

class breakout : public QWidget
{
    Q_OBJECT
    
public:
    breakout(QWidget *parent = 0);
    ~breakout();

protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void startGame();
    void pauseGame();
    void stopGame();
    void victory();
    void checkCollision();

private:
    ball* pball;
    paddle* ppaddle;
    brick* pbrick[30];
    int timeId;
    int x;
    bool gameOver;
    bool gameStarted;
    bool gameWon;
    bool gamePaused;
};

#endif // BREAKOUT_H
