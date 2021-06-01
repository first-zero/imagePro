#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>

class MainWindow;

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent, MainWindow* win);

signals:

public slots:

private:
    MainWindow* mainWindow;

    void init();
};

#endif // IMAGEWIDGET_H
