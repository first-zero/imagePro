#include "paintwidget.h"
#include <QMainWindow>
#include <QPainter>
#include <QPen>
PaintWidget::PaintWidget(QWidget *parent, MainWindow *win) : QLabel(parent)
{
    isDrawing = false;
    isMoving = false;
    isCutting = false;
    type = Null;
    lastPoint = endPoint = QPoint(0, 0);
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
//    Mat a = imageUtils->convertQImageToMat(image);
//    imshow("test" , a);
}

void PaintWidget::paintEvent(QPaintEvent *)
{
    // 使用 update 和show  能处理不能实时更新的问题
    update();
    QPainter painter(this);
    resize(image.size());
    if(isDrawing == true) {
        painter.drawImage(0, 0, tempImage);
    } else {
        painter.drawImage(0, 0, image);
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
    if(type != Pen && type != Null) {
        paint(image);
    }
    // 暂且用mainwin setImage property
    mainWindow->setImage(image);

}

void PaintWidget::mouseMoveEvent(QMouseEvent *e) {
    if(e->buttons() & Qt::LeftButton) { // 左键，正在移动
        isMoving = true;
        endPoint = e->pos();
        tempImage = image;
//        type = Pen;

        if(type == Pen) {
            paint(image);
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

    double ratePer = 0.5;

    double rate = 1 + way * ratePer;

    mainWindow->scale(rate, rate);

    mainWindow->setImage(image);
//    image = geomClass->scale(rate, rate, image);
    paint(image);
}

// 必须使用引用，否则对img的修改，影响不到参数外
void PaintWidget::paint(QImage& img)
{
    QPainter p(&img);
    QPen apen;
    apen.setWidth(5);
    apen.setColor(Qt::red);
    p.setPen(apen);
    int x1, x2, y1, y2;
    x1 = lastPoint.x(); x2 = endPoint.x();
    y1 = lastPoint.y(); y2 = endPoint.y();

    p.setRenderHint(QPainter::Antialiasing, true);

    switch(type) {
    case Pen:
        {
        p.drawLine(lastPoint, endPoint);
        lastPoint = endPoint;
        break;
    }
    case Ellipse:
    {
        p.drawEllipse(x1, y1, x2-x1, y2-y1);
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
        left = (y1<y2)? y1:y2;
        right = (y1>y2)? y1:y2;
        if(y1 < y2) {
            QPoint points[3] = {QPoint(left, bottom), QPoint(right, bottom), QPoint((right+left)/2, top)};
            p.drawPolygon(points, 3);
        } else {
            QPoint points[3] = {QPoint(left, top), QPoint(right, top), QPoint((right+left)/2, bottom)};
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

