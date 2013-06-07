#ifndef RICHEDIT_H
#define RICHEDIT_H

#include <QMainWindow>

namespace Ui {
class Richedit;
}

class Richedit : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Richedit(QWidget *parent = 0);
    ~Richedit();
    
private:
    Ui::Richedit *ui;
};

#endif // RICHEDIT_H
