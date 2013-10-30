#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    pGraph->paintGraph(painter);
}

void MainWindow::on_actionRandom_triggered()
{
    bool ok = false;
    size_t numberofNodes = QInputDialog::getInteger(this, tr("Random Graph"),tr("Number of Nodes:"),
                                                    20, 1, 1000, 1, &ok);
    if (!ok)
    {
        QMessageBox::critical(this, tr("Error"), tr("This value is invalid"));
        return;
    }

    size_t r = QInputDialog::getInteger(this, tr("Random Graph"), tr("Boarding Radius:"),
                                        10, 1, 1700, 1, &ok);
    if (!ok)
    {
        QMessageBox::critical(this, tr("Error"), tr("This value is invalid"));
        return;
    }

    int w = ui->centralWidget->width();
    int h = ui->centralWidget->height();
    //std::cout << w << std::endl;
    //std::cout << h << std::endl;
    pGraph->setWidthHeight(w, h);
    pGraph = new Graph(numberofNodes, r);
    //pGraph->printGraph();
    this->update();
}


void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}
