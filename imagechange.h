#ifndef IMAGECHANGE_H
#define IMAGECHANGE_H
#include <QImage>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;


class imageChange
{
public:
    imageChange();
    Mat convertQImageToMat(QImage img);

};

#endif // IMAGECHANGE_H
