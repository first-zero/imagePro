#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <mainwindow.h>
#include "paintwidget.h"
#include <QScrollArea>
#include <QDockWidget>

class MainWindow;

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent, MainWindow* win);
    enum Shape { Line, Points, PolyLine, Polygon, Rect, RoundedRect,
               Ellipse, Arc, Chord, Pie, Path, Text, Pixmap };
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    void setImage(QImage img);
    QImage getImage();

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *e);
private:
    MainWindow* mainWindow;
    QImage image;
    PaintWidget *imageLabel;
    QScrollArea *imgSrcollArea;
    QPainter* painter;
    QPen pen;
    Shape shape;
    QBrush brush;
    QPixmap pixmap;
    void init();
    void paint(QImage& theImage);


};

#endif // IMAGEWIDGET_H
