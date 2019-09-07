#ifndef MYLABEL_H
#define MYLABEL_H

#include <list>
#include <map>
#include<opencv2/opencv.hpp>
#include<QLabel>
#include<QPoint>
#include<QMouseEvent>
#include<QPainter>
#include<QWidget>
#include<QDebug>
#include<iostream>
#include<QString>
#include<QImage>


using namespace std;
using namespace cv;

class MyLabel : public QLabel
{
    Q_OBJECT
public:

    MyLabel(QWidget *parent = 0);
    void imgUpdate0();
    bool  isUpdate = 0;

protected:
    void  mousePressEvent(QMouseEvent *event);
    void  paintEvent(QPaintEvent *event);
    void  mouseMoveEvent(QMouseEvent *e);
    bool  isPressed = 0;


signals:
    void getStarPoint1(QPoint p);
    void getStopPoint(QPoint p);

private:
    QPoint starpoint;
    QPoint stoppoint;

};
#endif // MYLABEL_H
