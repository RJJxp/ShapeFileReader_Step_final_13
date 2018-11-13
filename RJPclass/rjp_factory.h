#ifndef RJP_FACTORY_H
#define RJP_FACTORY_H

#include "rjp_shape.h"
#include "QString"

class StaticFactory
{
public:
    static rjp_Shape * createShape(QString fp);
};

class rjp_Factory
{
public:
    virtual ~rjp_Factory(){}
    virtual rjp_Shape * createShape(QString fp) = 0;
    static rjp_Factory* getInstance();
protected:
    rjp_Factory(){}
    static rjp_Factory * myInstance;
};

class ESRI_Factory: public rjp_Factory
{
public:
    ESRI_Factory(){}
    virtual ~ESRI_Factory(){}
    virtual rjp_Shape *createShape(QString fp);

};

#endif // RJP_FACTORY_H
