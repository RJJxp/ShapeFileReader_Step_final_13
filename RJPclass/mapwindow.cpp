#include "mapwindow.h"

mapWindow::mapWindow(QMainWindow *parent) :QMainWindow(parent)
{
    this->setMinimumHeight(256);
    this->setMinimumWidth(256);
    this->setMaximumHeight(256);
    this->setMaximumWidth(256);

    // set the centralWidget
    myMapView = new mapView(this);
    this->setCentralWidget(myMapView);
}

void mapWindow::setMapVieW_Map(map* m)
{
    myMapView->setMap(m);
}
