#ifndef GEMO_H
#define GEMO_H
#include <QDockWidget>

class MainWindow;
class Geom : public QDockWidget
{
    Q_OBJECT
public:
    Geom(QWidget* parent, MainWindow* win);
    ~Geom();
    void init();
private:
    MainWindow* mainWindow;
};


#endif // GEMO_H
