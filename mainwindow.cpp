#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GrayGroup = new QButtonGroup(this);
    GrayGroup->addButton(ui->radioButton, 2);
    GrayGroup->addButton(ui->radioButton_2, 16);
    GrayGroup->addButton(ui->radioButton_3, 64);
    GrayGroup->addButton(ui->radioButton_4, 128);
    connect(ui->label0, SIGNAL(getStarPoint1(QPoint)), this, SLOT(getStarPoint(QPoint)));
    connect(ui->label0, SIGNAL(getStopPoint(QPoint)), this, SLOT(getStopPoint(QPoint)));
    connect(GrayGroup, SIGNAL(buttonClicked(int)), this, SLOT(GrayLevel(int)));
}

void MainWindow::on_pushButton_clicked()
{
    QString Qfilename = QFileDialog::getOpenFileName(this, tr("选择图像"), "", tr("Images (*.png *.bmp *.jpg)"));
    if (Qfilename.isEmpty() && isFirst_open)
    {
        QMessageBox::information(this, tr("打开图像失败"), tr("没有选择图片"));
        return;
    }
    else if(Qfilename.isEmpty() && !isFirst_open)
    {
        return;
    }
    else
    {
        filename = Qfilename.toStdString();
        srcImg0 = imread(filename);
        isFirst_open = 0;
    }

    QImage Qtemp;
    cvtColor(srcImg0, temp, COLOR_BGR2RGB);//BGR convert to RGB
    Qtemp = QImage((const unsigned char*)(temp.data), temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    ui->label0->setPixmap(QPixmap::fromImage(Qtemp));
    ui->label0->resize(Qtemp.size());
    ui->label0->show();
    ui->label0->imgUpdate0();
    haveRect = 0;
}

void MainWindow::on_pushButton_2_clicked()
{
    srcImg0.copyTo(srcImg);//后面srcImg会被修改，这里回到原图//
    //准备lookuptable改变图像灰阶//
    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.ptr();
    for (int i = 0; i <= 255; i++)
    {
        for (int j = 1; j <= grayLevel; j++)
        {
            if (i < (256 / grayLevel * j))
            {
                p[i] = 256 / (grayLevel - 1) * (j - 1);
                break;
            }

            if (i >= 255 - (256 / grayLevel))
            {
                p[i] = 255;
                break;
            }
        }
    }
    //判断是否打开图片//
    if (srcImg.empty())
    {
        QMessageBox::information(this, tr("错误"), tr("还没有打开任何图片"));
        return;
    }

    Mat grayImg(srcImg.rows, srcImg.cols, CV_8UC1);//单通道图片
    QImage Qtemp;

    if (haveRect)
    {
        int width = abs(starpoint.x() - stoppoint.x());
        int lenght = abs(starpoint.y() - stoppoint.y());

        if (stoppoint.x() < 0 || stoppoint.y() < 0
            || stoppoint.x() > srcImg.cols || stoppoint.y() > srcImg.rows)
        {
            QMessageBox::information(this, tr("错误"), tr("矩形超出图片范围"));
            return;
        }

        int x = starpoint.x() <= stoppoint.x() ? starpoint.x() : stoppoint.x();//获取矩形左上角x值//
        int y = starpoint.y() <= stoppoint.y() ? starpoint.y() : stoppoint.y();//获取矩形左上角y值//
        Mat roiImg = srcImg(Rect(x, y, width, lenght));
        Mat mask;
        srcImg(Rect(x, y, width, lenght)).copyTo(mask);
        cvtColor(mask, mask, COLOR_BGR2GRAY);
        LUT(mask, lookUpTable, mask);
        cvtColor(mask, mask, COLOR_GRAY2BGR);
        addWeighted(mask, 1, roiImg, 0, 0, roiImg);
        cvtColor(srcImg, temp, COLOR_BGR2RGB);
    }
    else
    {
        cvtColor(srcImg, grayImg, COLOR_BGR2GRAY);
        LUT(grayImg, lookUpTable, grayImg);//改变灰阶//
        cvtColor(grayImg, temp, COLOR_GRAY2RGB);//GRAY convert to RGB
    }

    Qtemp = QImage((const unsigned char*)(temp.data), temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    ui->label0->setPixmap(QPixmap::fromImage(Qtemp));
    ui->label0->resize(Qtemp.size());
    ui->label0->show();
    ui->label0->imgUpdate0();//变为灰度图后去除画的矩形//
    haveRect = 0;
}

void MainWindow::on_pushButton_3_clicked()
{
    QString Qfilename1 = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("Images (*.png *.bmp *.jpg)"));
    string filename1;
    if (Qfilename1.isEmpty())
    {
        QMessageBox::information(this, tr("保存图像失败"), tr("没有选择路径"));
        return;
    }

    else
    {
        filename1 = Qfilename1.toStdString();
        cvtColor(temp, temp, COLOR_RGB2BGR);
        imwrite(filename1, temp);
        QMessageBox::information(this, tr("保存结果"), tr("保存成功"));
    }


}

void MainWindow::getStarPoint(QPoint p)
{
    starpoint = p;
}

void MainWindow::getStopPoint(QPoint p)
{
    stoppoint = p;
    haveRect = 1;
}

void MainWindow::GrayLevel(int id)
{
    grayLevel = id;

}

MainWindow::~MainWindow()
{
    delete ui;
}
