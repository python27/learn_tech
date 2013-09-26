#include "dialog.h"
#include "ui_dialog.h"
#include <QtGui>
#include <QtCore>
#include <QMessageBox>
#include <QString>

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

void Dialog::on_pushButton_start_clicked()
{
    if (ui->radioButton_none->isChecked())
    {
        QMessageBox::information(this, "title", "NONE encode");

    }
    else if (ui->radioButton_ldpc->isChecked())
    {

        QString parameter1(ui->lineEdit_para_errorRate->text());
        QString parameter2(ui->lineEdit_para_codeRate->text());
        QString total = "LDPC encode :\n p1:" + parameter1 + "\n" + "p2 :" + parameter2;
        QMessageBox::information(this, "title", total);
        double channelErrorRate = ui->lineEdit_para_errorRate->text().toDouble();
        double codeRate = ui->lineEdit_para_codeRate->text().toDouble();

    }
    else if (ui->radioButton_lt->isChecked())
    {
        QMessageBox::information(this, "title", "LT encode");
    }
    else if (ui->radioButton_cascade->isChecked())
    {
        QMessageBox::information(this, "title", "Cascade encode");
    }
}
