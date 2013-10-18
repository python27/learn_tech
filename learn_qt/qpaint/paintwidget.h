#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include "shape.h"
#include "line.h"
#include "rect.h"
#include "graph.h"

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    void setCurrentShape(Shape::Code s)
    {
            if(s != currShapeCode) {
                    currShapeCode = s;
            }
    }


protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
        Shape::Code currShapeCode;
        Shape *shape;
        bool perm;
        QList<Shape*> shapeList;

        MyGraph mygraph;
        //MyGraph* pWidgetGraph;
};

#endif // PAINTWIDGET_H
