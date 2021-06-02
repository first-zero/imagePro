#ifndef MENUBAR_H
#define MENUBAR_H
#include <QMenuBar>
#include <QToolBar>
class MainWindow;

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

private:
    bool checkSave();

    MainWindow* mainWindow;
    QMenu* menu_file;
    QToolBar* toolbar;
    QImage image;
    QString fileName = nullptr;
    QAction* act_file_new, *act_file_open, *act_file_save, *act_file_saveAs,*act_file_exit;
};

#endif // MENUBAR_H
