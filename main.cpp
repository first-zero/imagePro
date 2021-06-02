#include "mainwindow.h"
#include <QApplication>
#include "opencv/highgui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    IplImage* img = cvLoadImage("D:\\work\\csz\\imagePro\\jobResult\\4.jpg");
    cvNamedWindow("abc",CV_WINDOW_AUTOSIZE);
    cvShowImage("abc",img);
    cvWaitKey(0);
    cvReleaseImage(&img);
    cvDestroyAllWindows();


    return a.exec();
}
