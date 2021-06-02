#include "imagewidget.h"
#include <QVBoxLayout>
#include <iostream>
ImageWidget::ImageWidget(QWidget *parent, MainWindow* win) : QWidget(parent)
{
    mainWindow = win;
    init();
}
void ImageWidget::init() {
//    this->adjustSize();
//    resize(QSize(600, 500));
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


}

void ImageWidget::setImage(QImage img) {

    // need command to delete memory
//    if(imageLabel)
//        delete imageLabel;
//    imageLabel->clear();
//    imageLabel->obje

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

//    imageLabel->show();
//    QLayout *ly = new QVBoxLayout(this);

//    ly->addWidget(imageLabel);
//    setLayout(ly);



}
QImage ImageWidget::getImage() {
    return this->image;
}

void ImageWidget::paintEvent(QPaintEvent *e) {
    update();

}
