#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include <QDockWidget>
#include "QListWidget"
#include "QStandardItemModel"
#include "QWidget"

namespace Ui {
class DockWidget;
}

class DockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit DockWidget(QWidget *parent = 0);
    ~DockWidget();
    void updateListView();
private:
    Ui::DockWidget *ui;
    QListWidget * myListWidget;
    QWidget * temWidget;

};

#endif // DOCKWIDGET_H
