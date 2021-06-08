#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif


#include "paintwidget.h"
#include <QMainWindow>
#include <QPainter>
#include <QPen>
#include <imagechange.h>
class ImageChange;

PaintWidget::PaintWidget(QWidget *parent, MainWindow *win) : QLabel(parent)
{
    isDrawing = false;
    isMoving = false;
    isCutting = false;
    type = Null;
    lastPoint = endPoint = QPoint(0, 0);
    enlargeOrScaleRate = 1.0;
    mainWindow = win;
    geomClass = new Geom;
    setAlignment(Qt::AlignCenter);
}

void PaintWidget::setShape(int shape) {
    this->type = shape;
}
QImage PaintWidget::getImage()
{
    if(image.isNull()!= true)
        return image;
    return QImage();
}

void PaintWidget::setImage(QImage img)
{

    image = img;
    tempImage = img;
    viewImage = image;
//    ImageChange imgChange;
//    cv::Mat a = imgChange.convertQImageToMat(image);
//    cv::imshow("te", a);
    enlargeOrScaleRate = 1.0;
//    Mat a = imageUtils->convertQImageToMat(image);
//    imshow("test" , a);
}

void PaintWidget::paintEvent(QPaintEvent *)
{
    // 使用 update 和show  能处理不能实时更新的问题
    update();
    QPainter painter(this);
//    resize(image.size());
    resize(viewImage.size());
    if(isDrawing == true) {
        painter.drawImage(0, 0, tempImage);
    } else {
        painter.drawImage(0, 0, viewImage);
    }
    show();

}

void PaintWidget::mousePressEvent(QMouseEvent *e) {
    if(e->button() == Qt::LeftButton) {
        lastPoint = e->pos();
        isDrawing = true;
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *e) {
    isDrawing = false;
    isMoving = false;
//    int x1, y1, x2, y2;
//    x1 = lastPoint.x();
    if(type != Pen && type != Null ) {
        paint(image);
        paint(viewImage);
    }
    // 暂且用mainwin setImage property
//    mainWindow->setImage(image);
//    viewImage = tempImage;
//    mainWindow->setImage(image);
}

void PaintWidget::mouseMoveEvent(QMouseEvent *e) {
    if(e->buttons() & Qt::LeftButton) { // 左键，正在移动
        isMoving = true;
        endPoint = e->pos();
        tempImage = viewImage;
//        type = Pen;

        if(type == Pen) {
            paint(viewImage);
            paint(image);
        }
        else if(type == Choose) {
//            isDrawing = false;
            return;
        }
        else {
            paint(tempImage);
        }

    }
}
void PaintWidget::wheelEvent(QWheelEvent *e) {
    if(type != PaintWidget::Choose)
        return;
//    e->pos(); e->delta();
    //  正向，远离用户为1 ， 负向靠近用户为0
//    QPoint numDegrees = event->angleDelta() / 8;
    int way= e->angleDelta().y() > 0? 1:-1;

    double ratePer = 0.4;
    if((enlargeOrScaleRate + way * ratePer) <= 0 ) {
        mainWindow->insertToOutputEdit(tr("当前缩放倍率为：%1 ,已不可再缩小").arg(enlargeOrScaleRate)) ;
        viewImage = geomClass->scale(enlargeOrScaleRate, enlargeOrScaleRate, image);

    //    mainWindow->setImage(image);
        tempImage = viewImage;
    //    paint(image);
//        paint(viewImage);

        return;
    }
    enlargeOrScaleRate = enlargeOrScaleRate + way * ratePer;
    mainWindow->insertToOutputEdit(tr("当前缩放倍率为：%1").arg(enlargeOrScaleRate)) ;

//    mainWindow->scale(enlargeOrScaleRate, enlargeOrScaleRate);
    viewImage = geomClass->scale(enlargeOrScaleRate, enlargeOrScaleRate, image);

//    mainWindow->setImage(image);
    tempImage = viewImage;
//    paint(image);
//    paint(viewImage);
}

// 必须使用引用，否则对img的修改，影响不到参数外
// 功能：修改img的数据，添加对应内容
void PaintWidget::paint(QImage& img)
{
    QPainter p(&img);
    QPen apen;
    apen.setWidthF(10.0);
    apen.setColor(Qt::red);
    p.setPen(apen);
    p.setRenderHint(QPainter::Antialiasing, true);


//    QPainter imageP(&image);
//    QPen apen1;
//    apen1.setWidth(5);
//    apen1.setColor(Qt::red);
//    imageP.setPen(apen1);
//    imageP.setRenderHint(QPainter::Antialiasing, true);

    // 反放缩率
    double tempRate = 1.0;
    if(img.cacheKey() == image.cacheKey() )  {
        tempRate = 1.0 / enlargeOrScaleRate;
//        apen.setWidth(apen.width()*tempRate);
//        apen.setWidthF(apen.width()*tempRate);
    }
    mainWindow->insertToOutputEdit(tr("apen width is ： %1 ").arg(cvFloor(apen.width()*tempRate)));
    apen.setWidth(cvFloor(apen.width()*tempRate));

    int x1, x2, y1, y2;
    x1 = cvRound(lastPoint.x() * tempRate); cvRound(x2 = endPoint.x() * tempRate);
    y1 = cvRound(lastPoint.y() * tempRate); cvRound(y2 = endPoint.y() * tempRate);

    switch(type) {
    case Pen:
        {
        p.drawLine(QPoint(x1, y1), QPoint(x2, y2));
//        QPoint lastImagePoint(lastPoint);
//        lastImagePoint/=enlargeOrScaleRate;
//        imageP.drawLine(lastPoint/enlargeOrScaleRate, endPoint/enlargeOrScaleRate);
        lastPoint = endPoint;
        break;
    }
    case Ellipse:
    {
        p.drawEllipse(x1, y1, x2-x1, y2-y1);
//        imageP.drawEllipse(x1/enlargeOrScaleRate, y1/enlargeOrScaleRate, (x2-x1)/enlargeOrScaleRate,
//                           (y2-y1)/enlargeOrScaleRate);
        break;
    }
    case Circle:
    {
        double length = (x2 - x1) >  (y2 - y1) ? (x2 - x1) : (y2 - y1);
        p.drawEllipse(x1, y1, length, length);
        break;
    }
    case Triangle:
    {
        int top, bottom, left, right;
        top = (y1 < y2)? y1:y2;
        bottom = (y1>y2)? y1:y2;
        left = (x1<x2)? x1:x2;
        right = (x1>x2)? x1:x2;
        if(y1 < y2) {
            QPoint points[3] = {QPoint(left, bottom), QPoint(right, bottom), QPoint((right+left)/2, top)};
            p.drawPolygon(points, 3);
        } else {
            QPoint points[3] = {QPoint(left, top), QPoint(right, top), QPoint((right+left)/2, bottom)};
            p.drawPolygon(points, 3);
        }
        break;
    }
    case Choose:
        break;
    }

//    p.drawImage(0, 0, image);
//    p.drawLine(0, 0,  300, 300);
//    p.drawEllipse(100, 100, 400, 400);
//    p.drawEllipse(50, 50, 500, 500);
//    mainWindow->insertToOutputEdit(tr("check format in paint() %d").arg(image.format()) );
    update();

}

