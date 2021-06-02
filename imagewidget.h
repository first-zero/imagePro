#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <mainwindow.h>
class MainWindow;

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent, MainWindow* win);

    void setImage(QImage img);
    QImage getImage();

signals:

public slots:

private:
    MainWindow* mainWindow;
    QImage image;
    QLabel *imageLabel;
    void init();
    void paintEvent(QPaintEvent *e);

};

#endif // IMAGEWIDGET_H
