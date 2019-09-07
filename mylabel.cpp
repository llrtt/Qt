#include "mylabel.h"


MyLabel::MyLabel(QWidget *parent) :QLabel(parent)
{

}

void MyLabel::mousePressEvent(QMouseEvent *e)
{
    isPressed = 1;
    starpoint = QPoint(e->x(), e->y());
    emit getStarPoint1(starpoint);
}

void MyLabel::mouseMoveEvent(QMouseEvent *e)
{
    if (isPressed)
    {
        stoppoint = QPoint(e->x(), e->y());
        emit getStopPoint(stoppoint);
        update();
    }

}


void MyLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);//必须有，才能让背景图片显示出来//
    if (!isUpdate)
    {
        QPainter painter(this);
        QPen pen;
        pen.setColor(Qt::green);
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawRect(starpoint.x(), starpoint.y(),
            stoppoint.x() - starpoint.x(), stoppoint.y() - starpoint.y());
    }
    else
    {
        isUpdate = 0;
    }
}

void MyLabel::imgUpdate0()
{
    isUpdate = 1;
    update();
}
