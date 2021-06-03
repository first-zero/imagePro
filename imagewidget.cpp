#include "imagewidget.h"
#include <QVBoxLayout>
#include <QtGlobal>
#include <iostream>
#include <QPainter>
#include <QPen>

ImageWidget::ImageWidget(QWidget *parent, MainWindow* win) : QWidget(parent)
{
    mainWindow = win;
    shape = Polygon;
//    pixmap.load(":/images/qt-logo.png");
    pixmap = QPixmap::fromImage(QImage(400, 400, QImage::Format_RGB888));

    // set background color to base which is white
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    init();
}
void ImageWidget::init() {

    painter = new QPainter(this);
    // make smoother
    painter->setRenderHint(QPainter::Antialiasing);
    // move painter to center of window
//    painter->translate(width()/2, height()/2);
    int side = qMin(width(), height());
    painter->scale(side/200.0, side/200.0);
    painter->setPen(Qt::NoPen);
    // 设置painter colar
    painter->setBrush(Qt::black);


    // init imageLabel 只需要一次，二次new会产生多个标签
    // Layout可以先设置好，再修改组件对象，同样是一次init
    imageLabel = new QLabel(this);

//    imageLabel->show();
    QLayout *ly = new QVBoxLayout(this);

    ly->addWidget(imageLabel);
    setLayout(ly);


    QImage img = QImage(700, 700, QImage::Format_RGB888);
    img.fill(Qt::white);
    this->image = img;
    setImage(img);
    painter->restore();
    update();

}

void ImageWidget::setImage(QImage img) {

    imageLabel->setAlignment(Qt::AlignCenter);

    // QLabel 设置位置
//    imageLabel->setGeometry(30, 30, 100, 30);
    image = img;
//    imageLabel
    imageLabel->clear();

    imageLabel->setPixmap(QPixmap::fromImage(image));

//    mainWindow->insertToOutputEdit(QString("Size: %1  %2 ").arg(image->width()).arg(image->height()));

//    mainWindow->insertToOutputEdit(tr("Size: 1 " ));

    imageLabel->setScaledContents(true);
    imageLabel->setStyleSheet("QLabl{border:2px solid rgb(220,220,220);}");
    imageLabel->resize(image.width(), image.height());
    resize(imageLabel->size());

    this->image = img;
    paint(image);
//    imageLabel->show();
//    QLayout *ly = new QVBoxLayout(this);

//    ly->addWidget(imageLabel);
//    setLayout(ly);
    update();

}

QSize ImageWidget::sizeHint() const {
    // 设置初始窗口大小
    return QSize(400, 200);
}
QSize ImageWidget::minimumSizeHint() const {
    return QSize(100, 100);
}


QImage ImageWidget::getImage() {
    return this->image;
}

void ImageWidget::paint(QImage& theImage) {
    QPainter p(&theImage);
    QPen apen;
    apen.setWidth(5);
    apen.setColor(Qt::black);
    p.setPen(apen);
    p.setRenderHint(QPainter::Antialiasing, true);

    p.drawRect(0, 0,  400, 400);
    update();
}
void ImageWidget::paintEvent(QPaintEvent *e) {
    QPainter painter(this);
    painter.drawImage(0, 0, image);
//    static const QPoint points[4] {
//        QPoint(10, 80),
//        QPoint(20, 10),
//        QPoint(80, 30),
//        QPoint(90, 70)
//    };
//    QRect rect(10, 20, 80, 60);
//    QPainterPath path;
//    path.moveTo(20, 80);
//    path.lineTo(20, 30);
//    path.cubicTo(80, 0, 50, 50, 80, 80);


//    int startAngle = 20 * 16;
//    int arcLength = 120 * 16;

//    painter = new QPainter(&pixmap);
//    painter->setPen(pen);
//    painter->setBrush(Qt::red);
//    painter->setBrush(brush);
////    if (antialiased)
////        painter.setRenderHint(QPainter::Antialiasing, true);
////    for(int x = 0; x < width(); x+=100) {
////        for(int y = 0; y < height(); y+=100) {
////            painter->save();
////            painter->translate(x, y);
////        }
////    }
//    painter->drawLine(QPoint(10, 10), QPoint(200, 200));
//    painter->begin(this);
//    painter->drawPixmap(0, 0, pixmap);


}
