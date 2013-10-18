#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    PaintWidget *paintWidget = new PaintWidget(this);
    setCentralWidget(paintWidget);

    connect(ui->actionDrawLine, SIGNAL(triggered()),
                    this, SLOT(on_actionDrawLine_triggered()));
    connect(ui->actionDrawRect, SIGNAL(triggered()),
                    this, SLOT(on_actionDrawRect_triggered()));
    connect(this, SIGNAL(changeCurrentShape(Shape::Code)),
                    paintWidget, SLOT(setCurrentShape(Shape::Code)));

    //connect(ui->actionDrawGraph, SIGNAL(triggered()),
    //        paintWidget, SLOT())


    //connect(ui->action)

    // HOW TODO IT // python27
    // connect(ui->actionMIE_Algo, SIGNAL(triggered()),
    //                paintWidget, SLOT());
}

MainWindow::~MainWindow()
{

    //delete pMainGraph;
    delete ui;
}

void MainWindow::on_actionDrawLine_triggered()
{
    emit changeCurrentShape(Shape::Line);
}

void MainWindow::on_actionDrawRect_triggered()
{
    emit changeCurrentShape(Shape::Rect);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About ControlApp"),
                       tr("<b>ControlApp</b> is an example software to demonstrates how to"
                          "plot the right graph and execute the right finding algorithm"));

}

void MainWindow::on_actionAboutQt_triggered()
{
    QMessageBox::aboutQt(this, "Qt");
}

void MainWindow::on_actionOpen_triggered()
{

     QString fileName = QFileDialog::getOpenFileName(this);
     if (fileName.isEmpty())
     {
         QMessageBox::warning(this, tr("Not Find File"), tr("please open a file"));
     }
     else
     {
        //do something, open file TODO
     }

}

void MainWindow::on_actionExit_triggered()
{
    close();
}


void MainWindow::on_actionRandom_triggered()
{
    pMainGraph = new MyGraph(50);
}
