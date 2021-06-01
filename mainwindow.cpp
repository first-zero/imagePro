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
    resize(QSize(1000, 800));
    QWidget *p = this->takeCentralWidget();
    if(p)
        delete p;
    setDockNestingEnabled(true);

    // menubar setup
    menuBar = new MenuBar(this, this);
    this->setMenuBar(menuBar);

    // image dock setup
    createImageWidget();
    createToolDock();
    createGemoDock();
    createOutputDock();

    this->setCentralWidget(dock_image);
    dock_image->adjustSize();


//    QHBoxLayout *lay = new QHBoxLayout();
//    lay->addWidget(dock_image);
//    lay->addWidget(dock_output);
//    setLayout(lay);

    // 排列dock
//    addDockWidget(Qt::LeftDockWidgetArea,dock_image);
    addDockWidget(Qt::LeftDockWidgetArea, dock_tool);
    addDockWidget(Qt::RightDockWidgetArea, dock_geom);
    addDockWidget(Qt::BottomDockWidgetArea,dock_output);


    // dock_image作为centralWidget，不能作为第一个参数，否则窗口会排列错误。
//    splitDockWidget(dock_output, dock_image, Qt::Vertical);
    splitDockWidget(dock_tool, dock_image, Qt::Horizontal);
    splitDockWidget(dock_image, dock_geom, Qt::Horizontal);

    splitDockWidget(dock_image, dock_output, Qt::Vertical);
//    splitDockWidget(dock_tool, dock_output, Qt::Vertical);
//    splitDockWidget(dock_geom, dock_output, Qt::Vertical);

//    splitDockWidget(dock_output, dock_geom, Qt::Vertical);

}

void MainWindow::createToolDock() {
    dock_tool = new QDockWidget("绘图栏", this);
//    dock_tool = new QDockWidget("工具箱", this);
    QWidget *widget = new QWidget(dock_tool);
    QToolBar *toolBar = new QToolBar("toolbar");
//    QToolButton* button1 = new QToolButton();
//    QToolButton* button2 = new QToolButton();
//    button1->setArrowType(Qt::LeftArrow);
//    button2->setArrowType(Qt::RightArrow);
//    buttton2->setIcon(new QIcon("icon2"));
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
//    toolBar->addWidget(button1);
//    toolBar->addWidget(button2);
    addToolBar(toolBar);

    toolBar->addWidget(widget);
//    dock_tool->setWidget(widget);
}
void MainWindow::createImageWidget() {
    // 没有this，则不是绑定在mainWindow上
    dock_image = new QDockWidget("图像",this);
    dock_image->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable); //指定停靠窗体的样式，此处为可移动
//    dock_image->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
//    dock_image->setGeometry(500, 0, 400, 400);
//    dock_image->setFixedWidth(200);
//    dock_image->setFixedHeight(200);
//    dock_image->setMinimumHeight(500);


    imageWidget = new ImageWidget(dock_image, this);
//  QVBoxLayout * a = new QVBoxLayout(imageWidget);
    QLabel *lb = new QLabel(this);
    lb->setAlignment(Qt::AlignCenter);

    // QLabel 设置位置
//    lb->setGeometry(30, 30, 100, 30);

    QImage *img = new QImage(300, 300, QImage::Format_RGB888);
    img->fill(0);
    lb->clear();
    lb->setPixmap(QPixmap::fromImage(*img));
    lb->setScaledContents(true);

    lb->resize(img->width(), img->height());


//    a->addWidget(lb);
//    imageWidget->setLayout(a);

    //    dock_image->setLayout(a);
    // 尝试使用 dock_image.setWidget，看能否解决窗口重叠问题
    //    dock_image->setWidget(imageWidget);
    dock_image->setWidget(lb);


}

void MainWindow::createOutputDock() {
    dock_output = new QDockWidget("输出", this);
    dock_output->setFeatures(QDockWidget::DockWidgetMovable); //指定停靠窗体的样式，此处为可移动
    dock_output->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    dock_output->setFixedWidth(this->size().width());


//    dock_output->resize(QSize(200, 300));
    QVBoxLayout * vlayout = new QVBoxLayout(dock_output);
//    QWidget *widget = new QWidget(dock_output);

    QTextEdit * outputEdit = new QTextEdit();
    outputEdit->setParent(dock_output);

//    outputEdit->resize(QSize(200, 200));
    outputEdit->resize(QSize(200,300));
    outputEdit->insertPlainText("dsfdafssssssssss\n\ns\n\nssdsdds");
    vlayout->addWidget(outputEdit);

//    dock_output->setLayout(vlayout);
    // 尝试
    dock_output->setWidget(outputEdit);




}


void MainWindow::createGemoDock() {
    dock_geom = new QDockWidget("几何变换", this);
    dock_geom->setFeatures(QDockWidget::DockWidgetMovable); //指定停靠窗体的样式，此处为可移动
    dock_geom->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    dock_geom->setFixedWidth(400);
    dock_geom->setFixedHeight(400);
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
MainWindow::~MainWindow()
{

    delete ui;
}
