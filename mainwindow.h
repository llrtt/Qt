#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <opencv2/opencv.hpp>
#include <QImage>
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <QScreen>
#include <QGuiApplication>
#include <cstring>
#include <string.h>
#include <QEvent>
#include "ui_mainwindow.h"
#include "mylabel.h"

using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int isFirst_open = 1;
    int isFirst_save = 1;
    Mat srcImg;
    Mat temp;
    string filename;
    QPoint starpoint;
    QPoint stoppoint;
    int grayLevel = 128;
    bool haveRect = 0;
    Mat srcImg0;

private:
    Ui::MainWindow *ui;
    QButtonGroup *GrayGroup;

signals:
    void Update();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void getStarPoint(QPoint p);
    void getStopPoint(QPoint p);
    void GrayLevel(int id);
};

#endif // MAINWINDOW_H
