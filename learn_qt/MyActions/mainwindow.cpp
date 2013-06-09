#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QtCore>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    label = new QLabel(this);
    bar = new QProgressBar(this);

    label->setText("python27");
    ui->statusBar->addPermanentWidget(label,0);
    ui->statusBar->addPermanentWidget(bar, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    ui->statusBar->showMessage("hello,world", 2000);
}
