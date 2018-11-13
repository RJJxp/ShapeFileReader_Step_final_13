#ifndef RJP_SHAPE_H
#define RJP_SHAPE_H

#include "shapelib/shapefil.h"
#include "rjp_dataset.h"
#include "QPainter"

class rjp_Shape
{
public:
    virtual ~rjp_Shape(){}
    virtual void drawSHP(QPainter * painter,double * box) const = 0;
    rjp_Shape * clone();
    rjp_DatasetPtr get_DatasetPtr();
protected:

    double * date2Screen(double x,double y,QPaintDevice * pic,double * dataBox) const;
    rjp_DatasetPtr DatasetPtr;
    rjp_Shape(rjp_DatasetPtr ds):DatasetPtr(ds){}
    /*
    datasetPtr = ds; // error occurs
    */
};

class rjp_Point:public rjp_Shape
{
public:
    rjp_Point(rjp_DatasetPtr ds):rjp_Shape(ds){}
    virtual ~rjp_Point(){}
    virtual void drawSHP(QPainter * painter, double *displaybox) const;
};

class rjp_Polyline:public rjp_Shape
{
public:
    rjp_Polyline(rjp_DatasetPtr ds):rjp_Shape(ds){}
    virtual ~rjp_Polyline(){}
    virtual void drawSHP(QPainter * painter, double *displayBox) const;
};

class rjp_Polygon:public rjp_Shape
{
public:
    rjp_Polygon(rjp_DatasetPtr ds):rjp_Shape(ds){}
    virtual ~rjp_Polygon(){}
    virtual void drawSHP(QPainter * painter, double *displaybox) const;
};
#endif // RJP_SHAPE_H
