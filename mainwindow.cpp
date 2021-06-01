#include <QMenuBar>
#include <QMenu>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QPixmap>

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
    CreateImageWidget();
    createOutputDock();
    createGemoDock();

    this->setCentralWidget(dock_image);

    QHBoxLayout *lay = new QHBoxLayout();
    lay->addWidget(dock_image);
    lay->addWidget(dock_output);
    setLayout(lay);
    // 排列dock
//    resizeDocks({dock_image, dock_output}, {20 , 40}, Qt::Vertical);
    splitDockWidget(dock_image, dock_geom, Qt::Horizontal);

    splitDockWidget(dock_image, dock_output, Qt::Vertical);

}

void MainWindow::CreateImageWidget() {
    dock_image = new QDockWidget("图像");
    dock_image->setFixedWidth(450);
    dock_image->setFixedHeight(450);



    imageWidget = new ImageWidget(dock_image, this);
    QVBoxLayout * a = new QVBoxLayout(imageWidget);
    QLabel *lb = new QLabel(imageWidget);

    // QLabel 设置位置
    lb->setGeometry(30, 30, 100, 30);

    QImage *img = new QImage(600, 600, QImage::Format_RGB888);
    img->fill(0);
    lb->clear();
    lb->setPixmap(QPixmap::fromImage(*img));

    lb->resize(img->width(), img->height());


    a->addWidget(lb);
    imageWidget->setLayout(a);
    dock_image->setLayout(a);

    this->addDockWidget(Qt::LeftDockWidgetArea,dock_image);

}

void MainWindow::createOutputDock() {
    dock_output = new QDockWidget("输出");
    dock_output->setFixedWidth(450);
    dock_image->setFixedHeight(450);


//    dock_output->resize(QSize(200, 300));
    QVBoxLayout * vlayout = new QVBoxLayout(dock_output);
//    QWidget *widget = new QWidget(dock_output);

    QTextEdit * outputEdit = new QTextEdit();
    outputEdit->setParent(dock_output);

//    outputEdit->resize(QSize(200, 200));
    outputEdit->resize(QSize(200,300));
//    outputEdit->setPlaceholderText("dsfdafssssssssss");
    outputEdit->insertPlainText("this is a test file");
    vlayout->addWidget(outputEdit);

    dock_output->setLayout(vlayout);
    this->addDockWidget(Qt::BottomDockWidgetArea,dock_output);



}


void MainWindow::createGemoDock() {
    dock_geom = new QDockWidget("几何变换");
    dock_geom->setFixedWidth(450);
    dock_geom->setFixedHeight(450);
    QGridLayout *gridLay = new QGridLayout(dock_geom);


    QLabel *label_name = new QLabel("图像名字:");
    QLabel *label_nameLine = new QLabel("图像1");
    QLabel *label_size = new QLabel("图像大小:");
    QLabel *label_sizeLine = new QLabel("200*300");
    gridLay->addWidget(label_name, 0, 0, 1, 1);
    gridLay->addWidget(label_nameLine, 0, 1, 1, 1);
    gridLay->addWidget(label_size, 1, 0, 1, 1);
    gridLay->addWidget(label_sizeLine, 1, 1, 1, 1);
    dock_geom->setLayout(gridLay);
    addDockWidget(Qt::RightDockWidgetArea, dock_geom);

}
MainWindow::~MainWindow()
{

    delete ui;
}
