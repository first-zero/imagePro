#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <Qlabel>
#include <QMainWindow>
#include <QPen>
#include <QPainter>
#include <QMouseEvent>
#include "geom.h"
#include "imagechange.h"
#include "mainwindow.h"
#include "opencv2/highgui.hpp"

class MainWindow;
class Geom;

class PaintWidget : public QLabel
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent, MainWindow *win);
    enum shape {
        Pen = 1, Line, Ellipse, Circle, Triangle, Rhombus,
        Rect, Square, Hexagon, Choose, Null};

    void setImage(QImage img);
    QImage getImage();
    void setPenWidth(int width) {
        penWidth = width;
    }
    void setPenColor(int color) {
        penColor = color;
    }
    void setShape(int shape);

signals:

public slots:

private:
    MainWindow* mainWindow;
    // image作为原图数据属性，tempImage作为画布缓冲数据，viewImage作为视图，作为原图缩放，修改的预览结果
    QImage image, tempImage;
    QImage  viewImage;
//    QPen apen;
    int penWidth;
    QColor penColor;
    QPoint lastPoint, endPoint;
    bool isDrawing, isMoving, isCutting;
    Geom *geomClass;
    ImageChange *imageUtils;
    int type;
    double enlargeOrScaleRate;


    void paintEvent(QPaintEvent *e);
    void paint(QImage& img);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
};

#endif // PAINTWIDGET_H
