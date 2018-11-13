#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "dockwidget.h"
#include "shpview.h"

#include "rjp_shapes.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    virtual void updateWhenShapesChange();

private slots:
    void openSHPfile();
    void createMap01();
    void createMap02();

private:
    Ui::MainWindow *ui;

    DockWidget * myLeftbar;
    shpView * myShpView;
};

#endif // MAINWINDOW_H
