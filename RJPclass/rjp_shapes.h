#ifndef RJP_SHAPES_H
#define RJP_SHAPES_H

#include "rjp_shape.h"
#include "QVector"
#include "QString"
#include "QPainter"

#include "rjp_shapes_command.hpp"

//class shapesObserver
//{
//public:
//    virtual ~shapesObserver(){}
//    virtual void updateWhenShapesChange() = 0;
//protected:
//    shapesObserver(){}

//};


class rjp_Shapes
{
public:
    // initializing
    rjp_Shapes();
    rjp_Shapes(shapesObCommand * obc);
    //rjp_Shapes(shapesObserver * ob );
    rjp_Shapes(rjp_Shapes * temShapes);
    rjp_Shape * at(int i) const;

    void setObCommand(shapesObCommand * obs);
    void addShapes(QStringList fp);
    void drawAllShapes(QPainter * painter) const;
    void notify();
    int getLayerSize() const;
    // void setOb(shapesObserver * ob);
    // serve for the 3rd initialization
    double * get_dataBox();
    QStringList get_pathList();

    ~rjp_Shapes();
private:
    shapesObCommand * obCommand;
    QVector<rjp_Shape *> myLayers;
    //shapesObserver * myOb;
    QStringList pathList;
    double * displayBox;

};


class singletonShapes
{
public:
    static rjp_Shapes* get_gData();
    static void release_gData();
private:
    static rjp_Shapes * gData;
};
#endif // RJP_SHAPES_H
