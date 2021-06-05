#include "paintwidget.h"
#include <QMainWindow>
#include <QPainter>
#include <QPen>
PaintWidget::PaintWidget(QWidget *parent, MainWindow *win) : QLabel(parent)
{
    isDrawing = false;
    isMoving = false;
    isCutting = false;
    type = -1;
    mainWindow = win;
    geomClass = new Geom;
    setAlignment(Qt::AlignCenter);
}

void PaintWidget::setShape(int shape) {
    this->type = shape;
}
QImage PaintWidget::getImage()
{
    return image;
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

    painter.drawImage(0, 0, image);
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

void PaintWidget::paint(QImage img)
{
    QPainter p(&img);
    QPen apen;
    apen.setWidth(5);
    apen.setColor(Qt::red);
    p.setPen(apen);

    p.setRenderHint(QPainter::Antialiasing, true);

    switch(type) {
    case Pen:
        {
        p.drawLine(lastPoint, endPoint);
        lastPoint = endPoint;
        break;
    }
    case Choose:
        break;
    }

//    p.drawImage(0, 0, image);
//    p.drawLine(0, 0,  300, 300);
//    p.drawEllipse(100, 100, 400, 400);
//    p.drawEllipse(50, 50, 500, 500);
    image = img;
//    mainWindow->insertToOutputEdit(tr("check format in paint() %d").arg(image.format()) );
    update();

}
