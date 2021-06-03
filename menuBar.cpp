#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

#include <QWidget>
#include <QMenu>
#include "mainwindow.h"
#include "MenuBar.h"
#include <QFile>
#include <QFileDialog>
#include <QImage>
#include <iostream>
#include <QMessageBox>
#include <QToolBar>
#include <QHBoxLayout>
#include <QPushButton>

using namespace  std;
MenuBar::MenuBar(QWidget* parent, MainWindow* win) :
    QMenuBar(parent)
{
    mainWindow = win;
    init();
}

void MenuBar::init() {
    menu_file = new QMenu();
    menu_file->setTitle("文件");

    act_file_new = new QAction(QString("新建"));
    act_file_open = new QAction(QString("打开"));
    act_file_save = new QAction(QString("保存"));
    act_file_saveAs = new QAction(QString("保存为"));
    act_file_new->setShortcuts(QKeySequence::New);
//    act_file_new->setToolTip("something");
    act_file_new->setStatusTip("new a file");

    this->addMenu(menu_file);
    menu_file->addAction(act_file_new);
    menu_file->addAction(act_file_open);
    menu_file->addAction(act_file_save);
    menu_file->addAction(act_file_saveAs);


//    QPushButton *button_new = new QPushButton(tr("新建"));
//    QPushButton *button_save = new QPushButton(tr("保存"));
//    button_new->setIcon(QIcon("/work/csz/imagePro/jobResult/4.jpg"));

//    QHBoxLayout *hlay = new QHBoxLayout();
//    hlay->addWidget(button_new);
//    hlay->addWidget(button_save);
////    toolbar->addAction(act_file_new);

//    QWidget *barWidget = new QWidget(mainWindow);
//    barWidget->setLayout(hlay);


    // toolbar init
    toolbar = new QToolBar("toolbar");
    act_file_new->setIcon(QIcon::fromTheme("image-new", QIcon("/work/csz/imagePro/jobResult/4.jpg")));
    toolbar->addAction(act_file_new);
    toolbar->addAction(act_file_open);
    toolbar->addAction(act_file_save);
    toolbar->addAction(act_file_saveAs);
//    toolbar->addWidget(barWidget);

    mainWindow->addToolBar(toolbar);

    connect(act_file_open, SIGNAL(triggered()), this, SLOT(fileOpen()));
    connect(act_file_new, &QAction::triggered, this, &MenuBar::fileNew);
    connect(act_file_save, &QAction::triggered, this, &MenuBar::fileSave);
    connect(act_file_saveAs, &QAction::triggered, this, &MenuBar::fileSaveAs);
}

void MenuBar::fileNew() {
    if(!checkSave()) {
        mainWindow->insertToOutputEdit(tr("取消fileNew操作"));
        return;
    }

    fileName.clear();
    image = QImage(600, 600, QImage::Format_RGB888);
    image.fill(Qt::white);
//    image.load("d:/work/csz/imagePro/jobResult/result1.png");
    // 使用set 不会立刻刷新
    mainWindow->setImage(image);
//    mainWindow->setPixmap(QPixmap::fromImage(image));
//    mainWindow->imageLabel->setPixmap(QPixmap::fromImage(image));

    update();
}
void MenuBar::fileOpen() {

    // 如果选择取消save,什么都不做
    if(!checkSave())
        return;

    fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "/work/csz/imagePro",
        tr("Image Files(*.png *.jpg *bmp)"));
    if(fileName.isEmpty()) {
        mainWindow->insertToOutputEdit(tr("文件名为空，读取失败"));
        return;
    }

    image = QImage();
    image.load(fileName);
    if(image.data_ptr() == nullptr) {
        QMessageBox::information(this, tr("错误"), tr("打开图像失败！"));
    }
    mainWindow->setImage(image);

    mainWindow->insertToOutputEdit(QString("open file, file path is %1").arg(fileName));
//    mainWindow->insertToOutputEdit(fileName);


}

void MenuBar::fileSave() {
    if(fileName.isEmpty()) {
        QString path = QFileDialog::getSaveFileName(this, tr("Save Image"), ".", tr("Images(*.jpg *.png *.bmp)"));
        if(!path.isEmpty()) {
            QImage image = mainWindow->getImage();
            image.save(path);
            mainWindow->insertToOutputEdit(tr("保存图像成功，路径为：%1").arg(path));
            fileName = path;

            mainWindow->setImage(image);
        }
    }
    else {
        QImage img = mainWindow->getImage();
        img.save(fileName);
        mainWindow->insertToOutputEdit(tr("保存图像成功，无需更改路径，路径为：%1").arg(fileName));
        mainWindow->setImage(image);

    }

}

void MenuBar::fileSaveAs() {
    QString path = QFileDialog::getSaveFileName(this, tr("save Image as"), "/work/csz/imagePro", tr("Images(*.jpg *.png *.bmp)"));
    if(!path.isEmpty()) {
        QImage image = mainWindow->getImage();
        image.save(path);
        mainWindow->insertToOutputEdit(tr("保存图像成功，更新路径为：%1").arg(path));
        fileName = path;
        image.load(path);
        mainWindow->setImage(image);
    }

}


bool MenuBar::checkSave() {
    return true;
}
MenuBar::~MenuBar() {

}
