#include "findcrap.h"
#include "ui_findcrap.h"
#include<QFile>
#include<QTextStream>
#include<QString>
#include<QTextCursor>

FindCrap::FindCrap(QWidget *parent) :QWidget(parent), ui(new Ui::FindCrap)
{
    ui->setupUi(this);
    getTextFile();
}

FindCrap::~FindCrap()
{
    delete ui;
}

void FindCrap::on_goButton_clicked()
{
    QString word = ui->lineEdit->text();
    ui->textEdit->find(word, QTextDocument::FindWholeWords);
}

void FindCrap::getTextFile()
{
    QFile myFile(":/ReadMe.txt");
    myFile.open(QIODevice::ReadOnly);

    QTextStream textStream(&myFile);
    QString line = textStream.readAll();

    myFile.close();

    ui->textEdit->setPlainText(line);

    QTextCursor textCursor = ui->textEdit->textCursor();
    textCursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);


}
