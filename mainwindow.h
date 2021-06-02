#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

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

    void setImage(QImage img);
    QImage getImage();
    void insertToOutputEdit(QString text);
    QString getOutputEditText();
private:
    Ui::MainWindow *ui;
    MenuBar* menuBar;
    QDockWidget* dock_image, *dock_output, *dock_geom, *dock_tool;
    ImageWidget *imageWidget;
    QTextEdit * outputEdit;
    QImage* image;

    void init();
    void createImageWidget();
    void createOutputDock();
    void createGemoDock();
    void createToolDock();
};

#endif // MAINWINDOW_H
