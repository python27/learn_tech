#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pGraph.reset(new Graph());
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
    Graph::setWidthHeight(w, h);
    //pGraph = new Graph(numberofNodes, r);
    //pGraph->printGraph();
    pGraph.reset(new Graph(numberofNodes, r));
    this->update();
}


void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionMIS_triggered()
{
    pGraph->MISAlgorithm();
    this->update();
}

void MainWindow::on_actionExample_triggered()
{
    int w = ui->centralWidget->width();
    int h = ui->centralWidget->height();
    pGraph->setWidthHeight(w, h);
    //pGraph = new Graph();
    //pGraph.reset(new Graph());
    this->update();
}

void MainWindow::on_actionMCDS_triggered()
{
    pGraph->MCDSAlgorithm();
    this->update();
}
