#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

#include <QMenuBar>
#include <QMenu>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QPixmap>
#include <QToolButton>
#include <QPushButton>
#include <QScrollArea>
#include <QToolBar>

#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "menuBar.h"
#include "imagewidget.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();

}
void MainWindow::init() {
    setWindowTitle("图像处理");
    resize(QSize(1400, 900));
    QWidget *p = this->takeCentralWidget();
    if(p)
        delete p;
    setDockNestingEnabled(true);

    // menubar setup
    menuBar = new MenuBar(this, this);
    this->setMenuBar(menuBar);

    // image dock setup
    createOutputDock();
    createImageWidget();
    createToolDock();
    createGemoDock();

    this->setCentralWidget(dock_image);
//    dock_image->adjustSize();


    // 排列dock
//    addDockWidget(Qt::LeftDockWidgetArea,dock_image);
    addDockWidget(Qt::BottomDockWidgetArea,dock_output);
    addDockWidget(Qt::LeftDockWidgetArea, dock_tool);
    addDockWidget(Qt::RightDockWidgetArea, dock_geom);


    // dock_image作为centralWidget，不能作为第一个参数，否则窗口会排列错误?。
//    splitDockWidget(dock_output, dock_image, Qt::Vertical);
    splitDockWidget(dock_tool, dock_image, Qt::Horizontal);
    splitDockWidget(dock_image, dock_geom, Qt::Horizontal);
    splitDockWidget(dock_image, dock_output, Qt::Vertical);

    // 尝试2
//    splitDockWidget(dock_tool, dock_geom, Qt::Horizontal);
//    splitDockWidget(dock_tool, dock_image, Qt::Horizontal);
//    insertToOutputEdit(QString("%1").arg(dock_output->width()));

}

void MainWindow::createToolDock() {
    dock_tool = new QDockWidget("绘图栏", this);
//    dock_tool = new QDockWidget("工具箱", this);

    QWidget *widget = new QWidget(dock_tool);

    QPushButton* button1 = new QPushButton("button1", widget);
    QPushButton* button2 = new QPushButton("button2", widget);
    button1->setToolTip("button1");
    button2->setToolTip("button1");
    button1->setFixedSize(60,40);
    button2->setFixedSize(60,40);
//    QGridLayout *gridlay = new QGridLayout(widget);
//    gridlay->addWidget(button1, 0, 0, 1, 1);
//    gridlay->addWidget(button2, 0, 1, 1, 1);
    QHBoxLayout *hlay = new QHBoxLayout(widget);
    hlay->addWidget(button1);
    hlay->addWidget(button2);
    widget->setLayout(hlay);

    dock_tool->setWidget(widget);
}
void MainWindow::createImageWidget() {
    // 没有this，则不是绑定在mainWindow上
    dock_image = new QDockWidget("图像",this);
    // QDockWidget::DockWidgetMovable |  可以拖拽  QDockWidget::DockWidgetFloatable 可脱离主窗口
    dock_image->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable); //指定停靠窗体的样式，此处为可移动
    dock_image->allowedAreasChanged(Qt::TopDockWidgetArea);
//    dock_image->setFeatures(QDockWidget::AllDockWidgetFeatures);
//    dock_image->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
//    dock_image->setGeometry(500, 0, 400, 400);
//    dock_image->setFixedWidth(200);
//    dock_image->setFixedHeight(200);
//    dock_image->setMinimumHeight(500);

//    dock_image->resize(700,700);

    imageWidget = new ImageWidget(dock_image, this);

//    QImage *img = new QImage(500, 500, QImage::Format_RGB888);
//    img->fill(Qt::blue);
//    imageWidget->setImage(*img);




    // QLabel 设置位置
//    lb->setGeometry(30, 30, 100, 30);

//    *lb = new QLabel(this);
//    lb->setAlignment(Qt::AlignCenter);

//    *image = new QImage(300, 300, QImage::Format_RGB888);
//    img->fill(0);
//    lb->clear();
//    lb->setPixmap(QPixmap::fromImage(*img));
//    lb->setScaledContents(true);

//    lb->resize(img->width(), img->height());


//    a->addWidget(lb);
//    imageWidget->setLayout(a);

    //    dock_image->setLayout(a);
    // 使用 dock_image.setWidget imageWidget，能解决窗口重叠问题,但窗口大小也有问题
    // 使用QScrollArea尝试
    QScrollArea *imgSrcollArea = new QScrollArea();
    imgSrcollArea->setBackgroundRole(QPalette::Dark);
    imgSrcollArea->setAlignment(Qt::AlignCenter);
    imgSrcollArea->setWidget(imageWidget);
    dock_image->setWidget(imgSrcollArea);

//        dock_image->setWidget(imageWidget);
//    dock_image->setWidget(imageWidget->imageLabel);
//    dock_image->resize(imageWidget->size());

}

void MainWindow::createOutputDock() {
    dock_output = new QDockWidget("输出", this);
    dock_output->adjustSize();
    dock_output->setFeatures(QDockWidget::DockWidgetMovable); //指定停靠窗体的样式，此处为可移动
    dock_output->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

//    int wid = this->size().width();
//    dock_output->setFixedWidth(this->size().width());
    dock_output->setMinimumHeight(120);
    dock_output->setMaximumHeight(300);
//    dock_output->setFixedHeight(200);

    outputEdit = new QTextEdit();
    outputEdit->setReadOnly(true);
    outputEdit->setParent(dock_output);

    outputEdit->resize(QSize(120,150));
    dock_output->resize(120, 200);
//    dock_output Sizehint()
//    outputEdit->setFixedHeight(150);

//    QScrollArea* outputScrollArea = new QScrollArea(dock_output);
//    outputScrollArea->setBackgro6undRole(QPalette::Highlight);
//    outputScrollArea->setAlignment(Qt::AlignCenter);
//    outputScrollArea->setWidget(outputEdit);

    insertToOutputEdit("dsfda");
    insertToOutputEdit("insert again");

    // 尝试
    dock_output->setWidget(outputEdit);



}


void MainWindow::createGemoDock() {
    dock_geom = new QDockWidget("几何变换", this);
    dock_geom->setFeatures(QDockWidget::DockWidgetMovable); //指定停靠窗体的样式，此处为可移动
    dock_geom->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock_image->setFeatures(QDockWidget::AllDockWidgetFeatures);

// 设定 fixedwidth 就无法手动拖拽窗口大小
//    dock_geom->setFixedWidth(400);
//    dock_geom->setFixedHeight(400);
    QGridLayout *gridLay = new QGridLayout(dock_geom);


    QLabel *label_name = new QLabel("图像名字:");
    QLabel *label_nameLine = new QLabel("图像1");
    QLabel *label_size = new QLabel("图像大小");
    QLabel *label_sizeLine = new QLabel("200*300");
    gridLay->addWidget(label_name, 0, 0, 1, 1);
    gridLay->addWidget(label_nameLine, 0, 1, 1, 1);
    gridLay->addWidget(label_size, 1, 0, 1, 1);
    gridLay->addWidget(label_sizeLine, 1, 1, 1, 1);
//    dock_geom->setLayout(gridLay);
    // 尝试
    QWidget *interWidget = new QWidget(dock_geom);
    interWidget->setLayout(gridLay);
    dock_geom->setWidget(interWidget);


}

QString MainWindow::getOutputEditText() {
    return outputEdit->toPlainText();
}

void MainWindow::insertToOutputEdit(QString text) {
    outputEdit->insertPlainText(text + tr("\n"));

}

void MainWindow::setImage(QImage img) {
    imageWidget->setImage(img);
}
QImage MainWindow::getImage() {
    return imageWidget->getImage();
}

MainWindow::~MainWindow()
{

    delete ui;
}
