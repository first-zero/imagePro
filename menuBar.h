#ifndef MENUBAR_H
#define MENUBAR_H
#include <QMenuBar>
#include <QToolBar>
#include "imagechange.h"

class MainWindow;
class ImageChange;

class MenuBar : public QMenuBar
{
    Q_OBJECT
public:
    MenuBar(QWidget* parent, MainWindow* win);
    ~MenuBar();
    void init();

private slots:
    void fileOpen();
    void fileSave();
    void fileNew();
    void fileSaveAs();
    void geomScaleBig();
    void geomScaleSmall();

private:
    bool checkSave();
    void menuFileInit();
    void menuGeomInit();


    ImageChange *imageUtils;
    MainWindow* mainWindow;
    QMenu* menu_file, *menu_geom;
    QToolBar* toolbar;
    QImage image;
    QString fileName = nullptr;
    QAction* act_file_new, *act_file_open, *act_file_save, *act_file_saveAs,*act_file_exit,
        *act_geom_scaleBig, *act_geom_scaleSmall;
};

#endif // MENUBAR_H
