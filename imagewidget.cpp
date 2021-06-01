#include "imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent, MainWindow* win) : QWidget(parent)
{
    mainWindow = win;
    init();
}
void ImageWidget::init() {
//    this->adjustSize();
    resize(QSize(500, 500));

}
