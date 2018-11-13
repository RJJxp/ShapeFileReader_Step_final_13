#include "shpview.h"

#include "QPainter"
#include "rjp_shapes.h"

shpView::shpView(QWidget *parent) : QWidget(parent)
{

}


void shpView::paintEvent(QPaintEvent *event)
{
    QPainter * painter = new QPainter(this);
    painter->begin(this);
    singletonShapes::get_gData()->drawAllShapes(painter);
    painter->end();
}
