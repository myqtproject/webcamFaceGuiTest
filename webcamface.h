#ifndef WEBCAMFACE_H
#define WEBCAMFACE_H

#include <QWidget>
#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

using namespace std;
using namespace cv;

namespace Ui {
class webcamFace;
}

class webcamFace : public QWidget
{
    Q_OBJECT
    
public:
    explicit webcamFace(QWidget *parent = 0);
    ~webcamFace();
    
//protected:
//    void faceDetectEvent(paintEvent *);

public slots:
    void theFrameGUIAndUpdate();

private slots:
    void on_faceDetect_clicked();
    void on_takePictures_clicked();

private:
    Ui::webcamFace *ui;
    //Camera Capture.
    VideoCapture cam;
    Mat frame;
    Mat frame_gray;
    Mat frameProcessed;
    //All Face Detection.
    vector<Rect> faces;
    CascadeClassifier face_cascade;
    //End of Detection.
    QImage srcimg;
    QTimer *timer;

};

#endif // WEBCAMFACE_H
