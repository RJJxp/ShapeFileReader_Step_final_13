#include "mapview.h"

#include "QPainter"

mapView::mapView(QWidget *parent) : QWidget(parent)
{
    _map = NULL;
}

void mapView::paintEvent(QPaintEvent *event)
{
    QPainter * painter = new QPainter(this);
    painter->begin(this);

    _map->draw(painter,rect());

    painter->end();

}

//void mapView::updateWhenShapesChange()
//{
//    this->update();
//}

void mapView::setMap(map *temMap)
{
    if(_map)
        delete _map;

    _map = temMap;
}
