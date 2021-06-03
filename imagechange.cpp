#include "imagechange.h"
#include<QImage>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

imageChange::imageChange()
{

}

Mat imageChange::convertQImageToMat(QImage image) {
    Mat mat;

    switch(image.format()) {
    case QImage::Format_RGB888:
        mat = Mat(image.height(), image.width(), CV_8UC3, (void *)image.constBits(), image.bytesPerLine()).clone();

        break;
    }
    return mat;
}

