#include "dialog.h"
#include "ui_dialog.h"
#include<QtGui>
#include<QtCore>
#include<QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

}


Dialog::~Dialog()
{
    delete ui;
}








void Dialog::on_pushButton_clicked()
{
    //info
    QMessageBox::information(this, "Message", "hello");
}

void Dialog::on_pushButton_2_clicked()
{
    QMessageBox::StandardButton  reply;
    reply = QMessageBox::question(this, "question", "do you like dog ?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QMessageBox::information(this, "Message", "you like dog");
    }
    else
    {
        QMessageBox::information(this, "Message", "you don't like dog");
    }
}

void Dialog::on_pushButton_3_clicked()
{
    QMessageBox::warning(this, "warning", "warning info.");
}



void Dialog::on_pushButton_4_clicked()
{
    QMessageBox::information(this, "custom", "custom info.", QMessageBox::Yes
                             | QMessageBox::YesToAll | QMessageBox::No | QMessageBox::NoToAll);
}
