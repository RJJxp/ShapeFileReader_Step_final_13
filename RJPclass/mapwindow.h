#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QWidget>
#include "QMainWindow"

#include "mapview.h"
#include "rjp_shapes.h"
#include "mapbuilder.h"

class mapWindow : public QMainWindow//,public QWidget
{
    Q_OBJECT
public:
    explicit mapWindow(QMainWindow *parent = nullptr);
    // this constructive function cannot have an implicit conversion
    // with a key word expicit to restrain
    void setMapVieW_Map(map * m);

private:
    mapView * myMapView;
};

#endif // MAPWINDOW_H
