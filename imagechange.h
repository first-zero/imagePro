#ifndef IMAGECHANGE_H
#define IMAGECHANGE_H
#include <QImage>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <QVector>
#include <QRgb>
#include <QDebug>
using namespace cv;


class ImageChange
{
public:
    ImageChange();
    Mat convertQImageToMat(QImage img);
    QImage convertMatToQImage(Mat matImage);

};

#endif // IMAGECHANGE_H
