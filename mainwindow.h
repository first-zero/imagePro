#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QScrollArea>
#include "PaintWidget.h"
#include "geom.h"
#include <QButtonGroup>

class MenuBar;
class ImageWidget;
class Geom;
class PaintWidget;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setImage(QImage img);
    QImage getImage();
    void insertToOutputEdit(QString text);
    QString getOutputEditText();
    QDockWidget* getDock_Image();
    void setPixmap(QPixmap map);

    PaintWidget *imageLabel;

public slots:
    void scale(double , double);
    void toolButtonClicked(int id);
    void saveImageData();
    void cancelImageData();
protected:

private:
    Ui::MainWindow *ui;
    MenuBar* menuBar;
    QDockWidget* dock_image, *dock_output, *dock_geom, *dock_tool;
    ImageWidget *imageWidget;
    QScrollArea *imgScrollArea;
    Geom *geomClass;
    QTextEdit * outputEdit;
    QImage image;
    QButtonGroup *toolbuttonGroup;
    int drawType;

    void init();
    void createImageWidget();
    void createOutputDock();
    void createGemoDock();
    void createToolDock();

};

#endif // MAINWINDOW_H
