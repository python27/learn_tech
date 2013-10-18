#include "paintwidget.h"
#include "graph.h"
#include <QColor>

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent), currShapeCode(Shape::Line), shape(NULL), perm(false)
{
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

}

void PaintWidget::paintEvent(QPaintEvent *event)
{
        QPainter painter(this);
        painter.setBrush(Qt::white);
        painter.drawRect(0, 0, size().width(), size().height());

        // BEGIN draw my graph
        painter.setBrush(Qt::black);
        painter.setPen(QColor(0,0,0));
        mygraph.paintMyGraph(painter);
        // END draw my graph


        foreach(Shape * shape, shapeList) {
                shape->paint(painter);
        }
        if(shape) {
                shape->paint(painter);
        }
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
        switch(currShapeCode)
        {
        case Shape::Line:
                {
                        shape = new Line;
                        break;
                }
        case Shape::Rect:
                {
                        shape = new Rect;
                        break;
                }
        }
        if(shape != NULL) {
                perm = false;
                shapeList<<shape;
                shape->setStart(event->pos());
                shape->setEnd(event->pos());
        }
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
        if(shape && !perm) {
                shape->setEnd(event->pos());
                update();
        }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
        perm = true;
}
