#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QWidget>
#include "shpview.h"
#include "mapbuilder.h"
#include "rjp_shapes.h"

// no need to inherit from the mapObserver
// cause once you click, you have already choosed which map you want
// i want this mapVieW changes when shapes changes

class mapView :public QWidget
{
    Q_OBJECT
public:
    explicit mapView(QWidget *parent = nullptr);

    void setMap(map * temMap);

    // inherit from the shpView
    virtual void paintEvent(QPaintEvent * event);

private:
    map * _map;
};

#endif // MAPVIEW_H
