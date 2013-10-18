#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "shape.h"
#include "paintwidget.h"
#include "graph.h"

class MyGraph;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    MyGraph* getGraphPointer() const
    {
        return pMainGraph;
    }

signals:
    void changeCurrentShape(Shape::Code newShape);
    
private slots:
    void on_actionDrawLine_triggered();

    void on_actionDrawRect_triggered();

    void on_actionAbout_triggered();

    void on_actionAboutQt_triggered();

    void on_actionOpen_triggered();

    void on_actionExit_triggered();

    void on_actionRandom_triggered();

private:
    Ui::MainWindow *ui;
    MyGraph *pMainGraph;
};

#endif // MAINWINDOW_H
