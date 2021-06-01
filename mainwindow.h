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
    QDockWidget* dock_image, *dock_output, *dock_geom, *dock_tool;
    ImageWidget *imageWidget;
    void init();
    void createImageWidget();
    void createOutputDock();
    void createGemoDock();
    void createToolDock();
};

#endif // MAINWINDOW_H
