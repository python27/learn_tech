#include<qapplication.h>
#include<qpushbutton.h>

int main( int argc, char** argv)
{
    QApplication a(argc, argv);

    QPushButton hello("Hello World!", 0);
    hello.resize(100, 30);
    hello.show();

    return a.exec();
}
