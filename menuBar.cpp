#include <QWidget>
#include <QMenu>
#include "mainwindow.h"
#include "MenuBar.h"

using namespace  std;
MenuBar::MenuBar(QWidget* parent, MainWindow* win) :
    QMenuBar(parent)
{
    mainWindow = win;
    init();
}

void MenuBar::init() {
    file = new QMenu();
    file->setTitle("文件");

    fileOpen = new QAction(QString("打开"));

    this->addMenu(file);
    file->addAction(fileOpen);
//    fileOpen->addAction("sdd");
}


MenuBar::~MenuBar() {

}
