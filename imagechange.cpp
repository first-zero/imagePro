#include "imagechange.h"
#include<QImage>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

ImageChange::ImageChange()
{

}

Mat ImageChange::convertQImageToMat(QImage image) {
    Mat mat;
    QImage swap = image.rgbSwapped();
//    int a = image.format();
    switch(image.format()) {
    case QImage::Format_RGB888:
        mat = Mat(swap.height(), swap.width(),
                  CV_8UC3, (void *)swap.constBits(), swap.bytesPerLine()).clone();

        break;
    case QImage::Format_Indexed8:
        mat = Mat(image.height(), image.width(), CV_8UC1,
                  const_cast<uchar*>(image.bits()), image.bytesPerLine()).clone();
        break;

    default:
        qDebug() << "Image format is not supported depth=%d and %d format/n",
                image.depth(), image.format();
        mat = Mat();
    }
    return mat;
}

QImage ImageChange::convertMatToQImage(Mat matImage) {
    int type = matImage.type();
    switch(type) {
    case CV_8UC1:
    {
//            image.setColorCount(256);
//            image.setColor(i, qRgb(i, i, i));
//            uchar *psrc = matImage.data;
//            for(int row = 0; row<matImage.rows; row++) {
//                uchar *pdest = image.scanLine(row);
//                memcpy(pdest, psrc, matImage.cols);
//                psrc += matImage.step;
//            }
        static QVector<QRgb> colorTable;
        if(colorTable.isEmpty()) {
            for(int i=0; i<256; i++)
                colorTable.push_back(qRgb(i, i, i));
        }
        QImage image(matImage.cols, matImage.rows, QImage::Format_Indexed8);
        image.setColorTable(colorTable);
        return image.copy();
    }
    case CV_8UC3:
    {
        const uchar *pchar = (const uchar*)matImage.data;
        QImage image(pchar, matImage.cols, matImage.rows, QImage::Format_RGB888);
        return image.rgbSwapped().copy();
    }
    case CV_8UC4:
    {
//        const uchar *pchar = (const uchar*) matImage.data;
//        QImage image(pchar, matImage.cols, matImage.rows,
//                     static_cast<qint32>(matImage.step),QImage::Format_ARGB32);
        // ???
//        return image.copy();
        break;
    }
    default:
        qDebug("Image format is not support:depth=%d and %d channels\n", matImage.depth(), matImage.channels());
    break;

    }

    // QImage 和 cv::mat 颜色是不同的`
    return QImage();
}

