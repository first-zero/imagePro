#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <Qlabel>
#include <QMainWindow>
#include <QPen>
#include <QPainter>
#include <QMouseEvent>
class PaintWidget : public QLabel
{
    Q_OBJECT
public:
    explicit PaintWidget(QWidget *parent, QMainWindow *win);
    void setImage(QImage img);
    QImage getImage();
    void setPenWidth(int width) {
        penWidth = width;
    }
    void setPenColor(int color) {
        penColor = color;
    }

signals:

public slots:

private:
    QMainWindow* mainWindow;
    QImage image, tempImage;
    QPen pen;
    int penWidth;
    QColor penColor;
    QPoint lastPoint, endPoint;
    bool isDrawing, isMoving, isCutting;
    int type;


    void paintEvent(QPaintEvent *e);
    void paint(QImage img);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
};

#endif // PAINTWIDGET_H
