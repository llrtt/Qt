#-------------------------------------------------
#
# Project created by QtCreator 2019-09-06T22:00:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



INCLUDEPATH += /usr/local/include/opencv4\
#/home/joker/opencv-4.0.0/build\


TARGET = GrayChange
TEMPLATE = app

LIBS += -lopencv_core\
-lopencv_imgcodecs\
-lopencv_imgproc\
-lopencv_highgui\
-lopencv_ml\
-lopencv_video\
-lopencv_features2d\
-lopencv_calib3d\
-lopencv_objdetect\
-lopencv_flann
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    mylabel.cpp

HEADERS += \
        mainwindow.h \
    mylabel.h

FORMS += \
        mainwindow.ui




