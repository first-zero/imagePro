#include "imagewidget.h"
#include <QVBoxLayout>
#include <QtGlobal>
#include <iostream>
#include <QPainter>
#include <QPen>
#include <QScrollArea>

ImageWidget::ImageWidget(QWidget *parent, MainWindow* win) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowStaysOnTopHint);

    mainWindow = win;

    // set background color to base which is white
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    init();
}
void ImageWidget::init() {

    //    pixmap.load(":/images/qt-logo.png");
//    pixmap = QPixmap::fromImage(QImage(400, 400, QImage::Format_RGB888));


    // init imageLabel 只需要一次，二次new会产生多个标签
    // Layout可以先设置好，再修改组件对象，同样是一次init
    imageLabel = new PaintWidget((QDockWidget*)parent(), mainWindow);
    // 图像完全填充标签
    imageLabel->setScaledContents(true);
    imgSrcollArea = new QScrollArea();
    imgSrcollArea->setBackgroundRole(QPalette::Dark);
    imgSrcollArea->setAlignment(Qt::AlignCenter);
//    imgSrcollArea->setWidget(imageLabel);
    imgSrcollArea->setWidget(this);
    ((QDockWidget*)parent())->setWidget(imgSrcollArea);
    this->setMaximumHeight(1080);
    this->setMaximumWidth(1920);


//    QLayout *ly = new QVBoxLayout(this);

//    ly->addWidget(imageLabel);
//    setLayout(ly);
//    QImage img = QImage(700, 700, QImage::Format_RGB888);
//    img.fill(Qt::green);
    QImage img;
    img.load("/work/csz/imagePro/jobResult/4.jpg");

    this->image = img;
    setImage(img);
//    imgSrcollArea->move((width() - imgSrcollArea->width())/2,
//                        (height() - imgSrcollArea->height())/2 );
    //    imgSrcollArea->resize(imageLabel->size());
//    imgSrcollArea->resize(size());
    imgSrcollArea->adjustSize();
    update();

}
void ImageWidget::setImage(QImage img) {


    // QLabel 设置位置
    imageLabel->setGeometry(30, 30, 100, 30);
    image = img;
//    imageLabel
//    imageLabel->clear();

//    imageLabel->setPixmap(QPixmap::fromImage(image));


//    imageLabel->setScaledContents(true);
//    imageLabel->setStyleSheet("QLabl{border:2px solid rgb(220,220,220);}");
//    imageLabel->resize(image.width(), image.height());
//    resize(imageLabel->size());

    imageLabel->setImage(image);
    this->resize(QSize(imageLabel->width(), imageLabel->height()));
    QSize sz = mainWindow->getDock_Image()->size();
    imgSrcollArea->resize(sz.width()-100, sz.height()-100);
//    imgSrcollArea->adjustSize();
//    imgSrcollArea->

//    imgSrcollArea->move((width() - imgSrcollArea->width())/2,
//                        (height() - imgSrcollArea->height())/2 );


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

void ImageWidget::paintEvent(QPaintEvent *) {

}
