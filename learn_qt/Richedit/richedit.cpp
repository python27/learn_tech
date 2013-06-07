#include "richedit.h"
#include "ui_richedit.h"

Richedit::Richedit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Richedit)
{
    ui->setupUi(this);
}

Richedit::~Richedit()
{
    delete ui;
}
