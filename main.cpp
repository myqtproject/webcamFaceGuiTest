#include <QApplication>
#include "webcamface.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    webcamFace w;
    w.show();
    
    return a.exec();
}
