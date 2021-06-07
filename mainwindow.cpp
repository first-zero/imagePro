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
//    splitDockWidget(dock_image, dock_output, Qt::Vertical);
    splitDockWidget(dock_tool, dock_output, Qt::Vertical);
    splitDockWidget(dock_geom, dock_output, Qt::Vertical);

    // 尝试2
//    splitDockWidget(dock_tool, dock_geom, Qt::Horizontal);
//    splitDockWidget(dock_tool, dock_image, Qt::Horizontal);
//    insertToOutputEdit(QString("%1").arg(dock_output->width()));

}

// 定义 pen, line, ellipse, circle, triangle, rhombus, rect, square, hexagon, choose
//      1       2   3       4       5           6       7       8      9        10
void MainWindow::createToolDock() {
    // init drawType
    drawType = -1;
    dock_tool = new QDockWidget("绘图栏", this);
    dock_tool->setFeatures(QDockWidget::DockWidgetClosable);

    QWidget *widget = new QWidget(dock_tool);

    QPushButton* button_pen = new QPushButton(QIcon("./image/toolbox/painbrush.png"),
                                                    "pen", this);
    QPushButton* button_line = new QPushButton(QIcon("./image/toolbox/painbrush.png"),
                                                    "line", this);
    QPushButton* button_ellipse = new QPushButton(QIcon("./image/toolbox/painbrush.png"),
                                                    "ellipse", this);
    QPushButton* button_circle = new QPushButton(QIcon("./image/toolbox/painbrush.png"),
                                                    "circle", this);
    QPushButton* button_triangle = new QPushButton(QIcon("./image/toolbox/painbrush.png"),
                                                    "triangle", this);
    QPushButton* button_rhombus = new QPushButton(QIcon("./image/toolbox/painbrush.png"),
                                                    "rhombus", this);
    QPushButton* button_rect = new QPushButton(QIcon("./image/toolbox/painbrush.png"),
                                                    "rect", this);
    QPushButton* button_square = new QPushButton(QIcon("./image/toolbox/painbrush.png"),
                                                    "square", this);
    QPushButton* button_hexagon = new QPushButton(QIcon("./image/toolbox/painbrush.png"),
                                                    "hexagon", this);
    QPushButton* button_choose = new QPushButton(QIcon("./image/toolbox/painbrush.png"),
                                                    "choose", this);

//    button_pen->setFixedSize(35, 35);
//    button_pen->setObjectName("customButton");

    button_pen->setToolTip("铅笔");
//    QGridLayout *gridlay = new QGridLayout(widget);
//    gridlay->addWidget(button1, 0, 0, 1, 1);
//    gridlay->addWidget(button2, 0, 1, 1, 1);
    QGridLayout *gridlay = new QGridLayout();
    gridlay->setAlignment(Qt::AlignTop);
    gridlay->addWidget(button_pen, 0, 0);
    gridlay->addWidget(button_line, 0, 1);
    gridlay->addWidget(button_ellipse, 1, 0);
    gridlay->addWidget(button_circle, 1, 1);
    gridlay->addWidget(button_triangle, 2, 0);
    gridlay->addWidget(button_rhombus, 2, 1);
    gridlay->addWidget(button_rect, 3, 0);
    gridlay->addWidget(button_square, 3, 1);
    gridlay->addWidget(button_hexagon, 4, 0);
    gridlay->addWidget(button_choose, 4, 1);

    toolbuttonGroup = new QButtonGroup();
    toolbuttonGroup->addButton(button_pen, 1);
    toolbuttonGroup->addButton(button_line, 2);
    toolbuttonGroup->addButton(button_ellipse, 3);
    toolbuttonGroup->addButton(button_circle, 4);
    toolbuttonGroup->addButton(button_triangle, 5);
    toolbuttonGroup->addButton(button_rhombus, 6);
    toolbuttonGroup->addButton(button_rect, 7);
    toolbuttonGroup->addButton(button_square, 8);
    toolbuttonGroup->addButton(button_hexagon, 9);
    toolbuttonGroup->addButton(button_choose, 10);
    QList<QAbstractButton *> buttons = toolbuttonGroup->buttons();
    foreach(QAbstractButton *button, buttons) {
        button->setFixedSize(35, 35);
        button->setObjectName("customButton");

    }

    connect(toolbuttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(toolButtonClicked(int)));

    widget->setLayout(gridlay);
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

    imageLabel = new PaintWidget(dock_image, this);
    QImage img = QImage(600, 600, QImage::Format_RGB888);
    img.fill(qRgb(255, 255, 255));
    imageLabel->setPenWidth(2);
    imageLabel->setPenColor(Qt::black);
    imageLabel->setImage(img);
//    imageLabel->setPixmap(QPixmap::fromImage(img));
    imageLabel->resize(img.width(), img.height());

\



    // QLabel 设置位置
//    lb->setGeometry(30, 30, 100, 30);

    // 使用 dock_image.setWidget imageWidget，能解决窗口重叠问题,但窗口大小也有问题
    // 使用QScrollArea尝试
    imgScrollArea = new QScrollArea();
    imgScrollArea->setBackgroundRole(QPalette::Dark);
    imgScrollArea->setAlignment(Qt::AlignCenter);
    imgScrollArea->setWidget(imageLabel);
    dock_image->setWidget(imgScrollArea);


//        dock_image->setWidget(imageWidget);
//    dock_image->setWidget(imageWidget->imageLabel);
//    dock_image->resize(imageWidget->size());

}

void MainWindow::createOutputDock() {
    dock_output = new QDockWidget("输出", this);
    dock_output->adjustSize();
//    dock_output->setFeatures(QDockWidget::DockWidgetMovable); //指定停靠窗体的样式，此处为可移动
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

    geomClass = new Geom;
    dock_geom->setMaximumWidth(300);
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
    image = img;
    imageLabel->setImage(img);
}
QImage MainWindow::getImage() {
    return imageLabel->getImage();

}
void MainWindow::scale(double rateH, double rateW) {
//    geomClass
//    insertToOutputEdit("scale processing");

    image = geomClass->scale(rateH, rateW, image);
    setImage(image);
}

void MainWindow::setPixmap(QPixmap map) {
    imageLabel->setPixmap(map);
}

// 绘图按钮点击事件
void MainWindow::toolButtonClicked(int id) {
    QList<QAbstractButton*> buttons = toolbuttonGroup->buttons();
    // 上一次使用的是pen，然后再点击按钮时，保存。
    if(drawType == PaintWidget::Pen)
        setImage(imageLabel->getImage());

    foreach(QAbstractButton *button, buttons) {

        if(toolbuttonGroup->button(id) != button) {
            button->setChecked(false);
            button->setStyleSheet("background-color:transparent");
        }
        else {
            if(drawType == id) {
                button->setChecked(false);
                button->setStyleSheet("background-color:transparent");
                imageLabel->setShape(PaintWidget::Null);
                drawType = 0;
                return;
            }
            drawType = id;
            button->setStyleSheet("background: rgb(76, 242, 255)");
        }
    }
    // 定义 pen, line, ellipse, circle, triangle, rhombus, rect, square, hexagon, choose
    //      1       2   3       4       5           6       7       8      9        10
//    QString toolBoxIndex[11] = {tr("Null"), tr("pen"), tr("line"), tr("ellipse"), tr("circle"), tr("triangle"),
//                    tr("rhombus"), tr("rect"), tr("square"), tr("hexagon"), tr("choose") };
//    imageLabel->setShape(tr("PaintWidget::") + toolBoxIndex[drawType]);
//    insertToOutputEdit(tr("使用绘图工具：") + toolBoxIndex[drawType]);
    switch(drawType) {
    case 0:
        imageLabel->setShape(PaintWidget::Null);
        insertToOutputEdit(tr("退出绘制模式"));
        break;
    case 1:
        imageLabel->setShape(PaintWidget::Pen);
        insertToOutputEdit(tr("使用绘图工具：铅笔"));
        break;
    case 2:
        imageLabel->setShape(PaintWidget::Line);
        insertToOutputEdit(tr("使用绘图工具：线"));
        break;
    case 3:
        imageLabel->setShape(PaintWidget::Ellipse);
        insertToOutputEdit(tr("使用绘图工具：椭圆"));
        break;
    case 4:
        imageLabel->setShape(PaintWidget::Circle);
        insertToOutputEdit(tr("使用绘图工具：圆"));
        break;
    case 5:
        imageLabel->setShape(PaintWidget::Triangle);
        insertToOutputEdit(tr("使用绘图工具：三角形"));
        break;
    case 6:
        imageLabel->setShape(PaintWidget::Rhombus);
        insertToOutputEdit(tr("使用绘图工具：菱形"));
        break;
    case 7:
        imageLabel->setShape(PaintWidget::Rect);
        insertToOutputEdit(tr("使用绘图工具：矩形"));
        break;
    case 8:
        imageLabel->setShape(PaintWidget::Square);
        insertToOutputEdit(tr("使用绘图工具：正方形"));
        break;
    case 9:
        imageLabel->setShape(PaintWidget::Hexagon);
        insertToOutputEdit(tr("使用绘图工具：六边形"));
        break;
    case 10:
        imageLabel->setShape(PaintWidget::Choose);
        insertToOutputEdit("使用缩放工具");
        break;
    }
}
QDockWidget* MainWindow::getDock_Image() {
    return dock_image;
}
MainWindow::~MainWindow()
{

    delete ui;
}
