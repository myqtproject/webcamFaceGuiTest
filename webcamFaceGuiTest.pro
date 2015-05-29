#-------------------------------------------------
#
# Project created by QtCreator 2015-04-10T17:51:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = webcamFaceGuiTest
TEMPLATE = app


SOURCES += main.cpp\
        webcamface.cpp

HEADERS  += webcamface.h

FORMS    += webcamface.ui

INCLUDEPATH += -I/usr/include/opencv

LIBS += -lopencv_core \
             -lopencv_highgui \
             -lopencv_imgproc \
             -lopencv_objdetect \


OTHER_FILES += \
    ../../../../usr/share/opencv/haarcascades/haarcascade_frontalface_default.xml
