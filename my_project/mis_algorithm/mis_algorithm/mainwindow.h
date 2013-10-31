#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent *);
    
private slots:
    void on_actionRandom_triggered();

    void on_actionQuit_triggered();

    void on_actionMIS_triggered();

    void on_actionExample_triggered();

private:
    Ui::MainWindow *ui;
    Graph* pGraph;
};

#endif // MAINWINDOW_H
