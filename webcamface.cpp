#include "webcamface.h"
#include "ui_webcamface.h"

#include "QtCore"
#include "QDebug"

#define FEAT_FACE_FILE "haarcascade_frontalface_default.xml"

RNG rng(12345);

webcamFace::webcamFace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::webcamFace)
{
    ui->setupUi(this);
    //Open the camera and check the camera connected.
    cam.open(0);
    if(cam.isOpened() == false){
        ui->camMessage->appendPlainText("Error: The camera is not connected !");
        return;
    }

    //--New the time and start.--//
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(theFrameGUIAndUpdate()));
    timer->start(30);

}

void webcamFace::theFrameGUIAndUpdate()
{
    //Read the capture.
    cam.read(frame);
    if(frame.empty() == true)
        return;

    inRange(frame, Scalar(0, 0, 175), Scalar(100, 100, 256), frameProcessed);
    GaussianBlur(frameProcessed, frameProcessed, Size(9, 9), 1.5);

    cvtColor(frame, frameProcessed, CV_BGR2RGB);

    QImage srcimg = QImage((const uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888).rgbSwapped();
    ui->webcamView->setPixmap(QPixmap::fromImage(srcimg));
}

webcamFace::~webcamFace()
{
    //Exit Application.
    cam.release();
    frame.release();
    timer->stop();
    delete ui;
}

void webcamFace::on_faceDetect_clicked()
{

    //Checking the XML files.
    QString xmlfile;
    if(face_cascade.empty())
    {
        xmlfile = tr("%1/%2").arg(QApplication::applicationDirPath()).arg(FEAT_FACE_FILE);
        if(!face_cascade.load(xmlfile.toLatin1().constData()))
            qDebug() << tr("Cannot find %1").arg(xmlfile);
    }

    cam >> frame;

    frame.copyTo(frame_gray);

    cvtColor(frame, frame_gray, CV_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    //Detect the faces.
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0|CV_HAAR_FIND_BIGGEST_OBJECT, Size(80, 80));

    for(size_t i = 0; i < faces.size(); i++)
    {
        int x = faces[i].x;
        int y = faces[i].y;
        int wid = faces[i].width;
        int hei = faces[i].height;

        Point face_point1(x, y);
        Point face_point2(x+wid, y+hei);

        rectangle(frame, face_point1, face_point2, Scalar(255, 0, 0), 3, 8, 0);
    }
    //End of Face Detect.

    QImage srcimg = QImage((const uchar*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888).rgbSwapped();
    ui->webcamView->setPixmap(QPixmap::fromImage(srcimg));
}

/*
 *
void webcamFace::on_takePictures_clicked()
{
    Mat faceimg;


    if(!get_image)
    {
        ui->camMessage->appendPlainText("Error: Failed to save the image!");
    }
}

*/
