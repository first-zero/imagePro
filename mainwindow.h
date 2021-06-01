#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MenuBar;
class ImageWidget;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MenuBar* menuBar;
    QDockWidget* dock_image, *dock_output, *dock_geom;
    ImageWidget *imageWidget;
    void init();
    void CreateImageWidget();
    void createOutputDock();
    void createGemoDock();

};

#endif // MAINWINDOW_H
