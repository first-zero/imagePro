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

class MainWindow;
class Geom;

class PaintWidget : public QLabel
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent, MainWindow *win);
    enum shape {
        Pen = 1, Line, Ellipse, Circle, Triangle, Rhomus,
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
    QImage image, tempImage;
    QPen apen;
    int penWidth;
    QColor penColor;
    QPoint lastPoint, endPoint;
    bool isDrawing, isMoving, isCutting;
    Geom *geomClass;
    ImageChange *imageUtils;
    int type;



    void paintEvent(QPaintEvent *e);
    void paint(QImage img);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
};

#endif // PAINTWIDGET_H
