#ifndef GEMO_H
#define GEMO_H
#include <QDockWidget>
#include "imagechange.h"
#include "opencv2/highgui.hpp"
using namespace cv;

class MainWindow;
class Geom
{
public:
    Geom();
    ~Geom();
    QImage scale(double rateW,double rateH, QImage image);
private:

    void init();
    MainWindow* mainWindow;
    ImageChange *imageUtils;
};


#endif // GEMO_H
