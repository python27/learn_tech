#include "breakout.h"
#include <QPainter>
#include <QApplication>
#include <iostream>

breakout::breakout(QWidget *parent)
    : QWidget(parent)
{
    x = 0;
    timeId = startTimer(100);
    gameStarted = true;
    gamePaused = false;
    gameWon = false;
    gameOver = false;

    pball = new ball();
    ppaddle = new paddle();

    int k = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            pbrick[k] = new brick(j * 40 + 30, i * 10 + 50);
            k++;
        }
    }
}

breakout::~breakout()
{
    delete pball;
    delete ppaddle;
    for (int i = 0; i < 30; i++)
    {
        delete pbrick[i];
    }
}

void breakout::paintEvent(QPaintEvent *event)
{
    std::cout<<"paint Event"<<std::endl;

    QPainter painter(this);

    if (gameOver)
    {
        QFont font("Courier", 15, QFont::DemiBold);
        QFontMetrics fm(font);
        int textwidth = fm.width("Game Over");

        painter.setFont(font);
        int h = height();
        int w = width();

        painter.translate(QPoint(w/2, h/2));
        painter.drawText(-textwidth/2, 0, "Game Over");
    }
    else if (gameWon)
    {
        QFont font("Courier", 15, QFont::DemiBold);
        QFontMetrics fm(font);
        int textwidth = fm.width("Victory");

        painter.setFont(font);
        int h = height();
        int w = width();

        painter.translate(QPoint(w/2, h/2));
        painter.drawText(-textwidth/2, 0, "Victory");
    }
    else
    {
        std::cout<<"repaint: draw Event"<<std::endl;
        painter.drawImage(pball->getRect(), pball->getImage());
        painter.drawImage(ppaddle->getRect(), ppaddle->getImage());

        for (int i = 0; i < 30; i++)
        {
            if (!pbrick[i]->isDestoryed())
            {
                painter.drawImage(pbrick[i]->getRect(), pbrick[i]->getImage());
            }
        }
    }
}

void breakout::timerEvent(QTimerEvent *event)
{
    std::cout<<"timer used"<<std::endl;
    pball->autoMove();
    checkCollision();
    repaint();
}

void breakout::keyPressEvent(QKeyEvent *event)
{

    std::cout<<"key Event"<<std::endl;
    switch (event->key())
    {
        case Qt::Key_Left:
        {
            int x = ppaddle->getRect().x();
            for (int i = 1; i <= 5; i++)
            {
                ppaddle->moveLeft(x--);
            }
            break;
        }
        case Qt::Key_Right:
        {
            int x = ppaddle->getRect().x();
            for (int i = 1; i <= 5; i++)
            {
                ppaddle->moveRight(x++);
            }
            break;
        }
        case Qt::Key_P:
        {
            pauseGame();
            break;
        }
        case Qt::Key_Space:
        {
            startGame();
            break;
        }
        case Qt::Key_Escape:
        {
            qApp->exit();
            break;
        }
        default:
        {
            QWidget::keyPressEvent(event);
        }
    }
}

void breakout::startGame()
{
    std::cout<<"start Game"<<std::endl;
    if (!gameStarted)
    {
        ppaddle->resetStatus();
        pball->resetStatus();
        for (int i = 0; i < 30; i++)
        {
            pbrick[i]->setDestoryed(false);
        }
        gameStarted = true;
        gameOver = false;
        gameWon = false;
        timeId = startTimer(100);
    }
}

void breakout::pauseGame()
{
    std::cout<<"pause game"<<std::endl;
    if (gamePaused)
    {
        timeId = startTimer(100);
        gamePaused = false;

    }
    else
    {
        gamePaused = true;
        killTimer(timeId);
    }
}

void breakout::stopGame()
{
    std::cout<<"stop game"<<std::endl;
    killTimer(timeId);
    gameOver = true;
    gameStarted = false;
}

void breakout::victory()
{
    killTimer(timeId);
    gameWon = true;
    gameStarted = false;
}

void breakout::checkCollision()
{
    std::cout<<"check collision"<<std::endl;

    // ball collise to the bottom, fail
    if ((pball->getRect()).bottom() > 400)
    {
        stopGame();
    }

    // all bricks are destroyed, victory.
    int sum = 0;
    for (int i = 0; i < 30; i++)
    {
        if (pbrick[i]->isDestoryed())
        {
            sum++;
        }
    }
    if (sum == 30)
    {
        victory();
    }

    // the ball collise to the paddle
    if ((pball->getRect()).intersects(ppaddle->getRect()))
    {
        int ppaddleLeftPos = (ppaddle->getRect()).left();
        int first = ppaddleLeftPos + 8;
        int second = ppaddleLeftPos + 16;
        int third = ppaddleLeftPos + 24;
        int fourth = ppaddleLeftPos + 32;

        int pballLeftPos = (pball->getRect()).left();

        if (pballLeftPos < first)
        {
            pball->setXdir(-1);
            pball->setYdir(-1);
        }

        if (pballLeftPos >= first && pballLeftPos < second)
        {
            pball->setXdir(-1);
            pball->setYdir(-1 * pball->getYdir());
        }

        if (pballLeftPos >= second && pballLeftPos < third)
        {
            pball->setXdir(0);
            pball->setYdir(-1);
        }

        if (pballLeftPos >= third && pballLeftPos < fourth)
        {
            pball->setXdir(1);
            pball->setYdir(-1 * pball->getYdir());
        }

        if (pballLeftPos >= fourth)
        {
            pball->setXdir(1);
            pball->setYdir(-1);
        }
    }

    // the ball collised to the bricks
    for (int i = 0; i < 30; i++)
    {
        if ((pball->getRect()).intersects(pbrick[i]->getRect()))
        {
            int pballLeft = pball->getRect().left();
            int pballTop = pball->getRect().top();
            int pballWidth = pball->getRect().width();
            int pballHeight = pball->getRect().height();

            QPoint pointLeft(pballLeft - 1, pballTop);
            QPoint pointRight(pballLeft + pballWidth + 1, pballTop);
            QPoint pointTop(pballLeft, pballTop - 1);
            QPoint pointBottom(pballLeft, pballTop + pballHeight + 1);

            if (!pbrick[i]->isDestoryed())
            {
                if ((pbrick[i]->getRect()).contains(pointRight))
                {
                    pball->setXdir(-1);
                }
                if ((pbrick[i]->getRect()).contains(pointLeft))
                {
                    pball->setXdir(1);
                }
                if ((pbrick[i]->getRect()).contains(pointTop))
                {
                    pball->setYdir(1);
                }
                if ((pbrick[i]->getRect()).contains(pointBottom))
                {
                    pball->setYdir(-1);
                }

                pbrick[i]->setDestoryed(true);
            }

        }

    }
}
