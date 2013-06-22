#include "breakout.h"
#include <QApplication>
#include <QDesktopWidget>

void center(QWidget &widget)
{
    int WIDTH = 300;
    int HEIGHT = 400;

    int screenwidth;
    int screenheight;
    int x, y;

    QDesktopWidget *pdesktop = QApplication::desktop();
    screenwidth = pdesktop->width();
    screenheight = pdesktop->height();

    x = (screenwidth - WIDTH) / 2;
    y = (screenheight - HEIGHT) / 2;

    widget.setGeometry(x, y, WIDTH, HEIGHT);
    widget.setFixedSize(WIDTH, HEIGHT);
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    breakout window;
    window.setWindowTitle("Breakout Game");
    window.show();
    center(window);

    return app.exec();
}
