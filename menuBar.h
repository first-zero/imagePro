#ifndef MENUBAR_H
#define MENUBAR_H
#include <QMenuBar>

class MainWindow;

class MenuBar : public QMenuBar
{
    Q_OBJECT
public:
    MenuBar(QWidget* parent, MainWindow* win);
    ~MenuBar();
    void init();
private:
    MainWindow* mainWindow;
    QMenu* file;
    QAction* fileNew, *fileOpen, *fileSave, *fileSaveAs,*fileExit;
};

#endif // MENUBAR_H
