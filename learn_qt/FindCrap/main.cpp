#include <QApplication>
#include "findcrap.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FindCrap w;
    w.show();
    
    return a.exec();
}
