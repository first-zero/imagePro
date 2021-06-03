#include "paintwidget.h"
#include <QMainWindow>
#include <QPainter>
#include <QPen>
PaintWidget::PaintWidget(QWidget *parent, QMainWindow *win) : QLabel(parent)
{
    isDrawing = false;
    isMoving = false;
    isCutting = false;
    type = -1;
    mainWindow = win;
    setAlignment(Qt::AlignCenter);
}


QImage PaintWidget::getImage()
{
    return image;
}

void PaintWidget::setImage(QImage img)
{
    image = img;
//    resize(img.size());
//    paint(img);
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
}

void PaintWidget::mouseMoveEvent(QMouseEvent *e) {

}

void PaintWidget::paint(QImage img)
{
    QPainter p(&img);
    QPen apen;
    apen.setWidth(5);
    apen.setColor(Qt::red);
    p.setPen(apen);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.drawImage(0, 0, image);
//    p.drawLine(0, 0,  300, 300);
//    p.drawEllipse(100, 100, 400, 400);
//    p.drawEllipse(50, 50, 500, 500);
    image = img;
    update();

}
