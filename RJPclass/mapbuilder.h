#ifndef MAPBUILDER_H
#define MAPBUILDER_H

#include "QPainter"
#include "rjp_shapes.h"

class mapObserver
{
public:
    virtual void updateWhenMapChange()=0;
    // mapWindow will inherit from mapObserve
};

// gridline
class gridLine
{
public:
    virtual ~gridLine(){}
    virtual void draw(QPainter * painter,QRect rc) =0;
};

class gridLineSolid: public gridLine
{
public:
    virtual ~gridLineSolid(){}
    virtual void draw(QPainter * painter,QRect rc)
    {
        painter->setPen(QPen(Qt::SolidLine));

        int gap = rc.height()/10;

        for(int i=0; i<rc.height()/gap; i++)
            for(int j=0; j<rc.width()/gap; j++)
            painter->drawRect(QRect(QPoint(gap* j, gap* i), QSize(gap, gap)));
    }
};

class gridLineDot: public gridLine
{
public:
    virtual ~gridLineDot(){}
    virtual void draw(QPainter * painter,QRect rc)
    {
        painter->setPen(QPen(Qt::black));
        painter->setPen(QPen(Qt::DotLine));

        int gap = rc.height()/10;

        for(int i=0; i<rc.height()/gap; i++)
            for(int j=0; j<rc.width()/gap; j++)
            painter->drawRect(QRect(QPoint(gap* j, gap* i), QSize(gap, gap)));

        painter->setPen(QPen(Qt::SolidLine));
    }
};

// scaleBar
class scaleBar
{
public:
    virtual ~scaleBar(){}
    virtual void draw(QPainter* painter, QRect rc)=0;
protected:
    scaleBar(){}
};

class scaleBarText:public scaleBar
{
public:
    virtual ~scaleBarText(){}
    virtual void draw(QPainter* painter, QRect rc)
    {
        painter->drawText( QRectF( QPointF(rc.width() - 30, rc.height()-10), QSize(30,10) ),
                           "1 : " + QString::number((double)(1.0/1.0),'g', 2) );
    }
};

class scaleBarGraphic:public scaleBar
{
public:
    virtual ~ scaleBarGraphic(){}
    virtual void draw(QPainter* painter, QRect rc)
    {
        painter->setBrush( QBrush( Qt::red , Qt::SolidPattern));
        painter->drawRect( QRect( QPoint(rc.width() - 30, rc.height()-10), QSize(10,5) ) );
        painter->setBrush( QBrush( Qt::green , Qt::SolidPattern));
        painter->drawRect( QRect( QPoint(rc.width() - 20, rc.height()-10), QSize(10,5) ) );
    }
};

// northPointer
class northPointer
{
public:
    virtual ~northPointer(){}
    virtual void draw(QPainter* painter, QRect rc)=0;
protected:
    northPointer(){}
};

class northPointerArrow:public northPointer
{
public:
    virtual ~northPointerArrow(){}
    virtual void draw(QPainter* painter, QRect rc)
    {
        QPen pen(Qt::black);
        pen.setWidth(3);
        painter->setPen(pen);
        painter->drawLine(QPoint(rc.width()-20, 10), QPoint(rc.width()-25,15));
        painter->drawLine(QPoint(rc.width()-20, 10), QPoint(rc.width()-15,15));
        painter->drawLine(QPoint(rc.width()-20, 10), QPoint(rc.width()-20,30));
    }
};

class northPointer3D:public northPointer
{
public:
    virtual ~northPointer3D(){}
    virtual void draw(QPainter* painter, QRect rc)
    {
        painter->setBrush( QBrush( Qt::black , Qt::SolidPattern));
        QVector<QPoint> points;
        points.push_back(QPoint(rc.width()-20, 10));
        points.push_back(QPoint(rc.width()-20, 15));
        points.push_back(QPoint(rc.width()-25, 30));
        painter->drawPolygon(QPolygon(points));

        points.clear();
        points.push_back(QPoint(rc.width()-20, 10));
        points.push_back(QPoint(rc.width()-20, 15));
        points.push_back(QPoint(rc.width()-15, 30));
        painter->drawPolygon(QPolygon(points));

    }
};

// map
class map
{
public:
    virtual ~map(){}
    virtual void draw(QPainter* painter, QRect rc)=0;

    //void setObserver(mapObserver * ob){_observer = ob;}
    //void notify(){_observer->updateWhenMapChange();}

    northPointer * _northPointer;
    scaleBar * _scaleBar;
    gridLine * _gridLine;
    //mapObserver * _observer;

    rjp_Shapes * _shapes;

protected:

    map()
    {
        _northPointer = NULL;
        _scaleBar = NULL;
        _gridLine = NULL;
        //_observer = NULL;
        _shapes = NULL;
    }
};

class mapWithoutGridLine:public map
{
public:
    virtual ~mapWithoutGridLine(){}
    virtual void draw(QPainter *painter, QRect rc)
    {
        _scaleBar->draw(painter,rc);
        _northPointer->draw(painter,rc);
        _shapes->drawAllShapes(painter);
    }
};

class mapWithAllElements:public map
{
public:
    virtual ~mapWithAllElements(){}
    virtual void draw(QPainter *painter, QRect rc)
    {
        _gridLine->draw(painter,rc);
        _scaleBar->draw(painter,rc);
        _northPointer->draw(painter,rc);
        _shapes->drawAllShapes(painter);
    }
};


// mapBuilder
class mapBuilder
{
public:
    virtual ~ mapBuilder(){}

    // polymorphism
    virtual void buildMap() = 0;
    virtual void buildGridLine() =0;
    virtual void buildScaleBar() =0;
    virtual void buildNorthPointer() =0;

    // function
    void  buildShapes(rjp_Shapes * temShapes);
    map * getMap(){return _map;}
protected:
    mapBuilder(){}
    map * _map;

};

class mapWithoutGridLineBuilder:public mapBuilder
{
public:
    mapWithoutGridLineBuilder(){}
    virtual ~mapWithoutGridLineBuilder(){}

    virtual void buildMap()
    {
        _map = new mapWithoutGridLine();
    }

    virtual void buildGridLine()
    {
        _map->_gridLine=NULL;
    }

    virtual void buildScaleBar()
    {
        _map->_scaleBar = new scaleBarGraphic();
    }

    virtual void buildNorthPointer()
    {
        _map->_northPointer =new northPointerArrow();
    }
};

class mapWithAllElementsBuilder:public mapBuilder
{
public:
    mapWithAllElementsBuilder(){}
    virtual ~mapWithAllElementsBuilder(){}

    virtual void buildMap()
    {
        _map = new mapWithAllElements();
    }

    virtual void buildGridLine()
    {
        _map->_gridLine = new gridLineSolid();
    }

    virtual void buildNorthPointer()
    {
        _map->_northPointer = new northPointer3D();
    }

    virtual void buildScaleBar()
    {
        _map->_scaleBar = new scaleBarGraphic();
    }
};


class mapDirector
{
public:
    mapDirector(mapBuilder* builder){_builder = builder;}
    map * constructMap(rjp_Shapes * temShapes)
    {
        _builder->buildMap();
        _builder->buildShapes(temShapes);
        _builder->buildGridLine();
        _builder->buildNorthPointer();
        _builder->buildScaleBar();
        return _builder->getMap();
    }

private:
    mapBuilder * _builder;
};
#endif // MAPBUILDER_H
