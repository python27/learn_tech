#include <QApplication>
#include "richedit.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Richedit w;
    w.show();
    
    return a.exec();
}
