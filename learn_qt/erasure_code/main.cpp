#include "dialog.h"
#include <QApplication>
#include <QTextCodec>


int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("gb18030"));
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    
    return a.exec();
}
