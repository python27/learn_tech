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

    ui->treeWidget->setColumnCount(2);
    ui->treeWidget->setHeaderLabels(QStringList()<<"one"<<"two");

    addRoot("1 Hello", "World");
    addRoot("2 Hello", "World");
    addRoot("3 Hello", "World");

}


Dialog::~Dialog()
{
    delete ui;
}


void Dialog::addRoot(QString name, QString description)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0, name);
    item->setText(1, description);
    ui->treeWidget->addTopLevelItem(item);


    addChild(item, "one", "hello");
    addChild(item, "two", "hello");
}


void Dialog::addChild(QTreeWidgetItem *parent,QString name, QString description)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(parent);
    item->setText(0, name);
    item->setText(1, description);
    parent->addChild(item);
}



void Dialog::on_pushButton_clicked()
{
    ui->treeWidget->currentItem()->setBackgroundColor(0, Qt::red);
    ui->treeWidget->currentItem()->setBackgroundColor(1, Qt::blue);
}
