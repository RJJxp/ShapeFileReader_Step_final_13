#include "rjp_factory.h"

#include "rjp_shape.h"
#include "rjp_dataset.h"

// initialize the static
rjp_Factory * rjp_Factory::myInstance = NULL;
// ====================================================================

rjp_Factory * rjp_Factory::getInstance()
{
    if(!myInstance)
    {
        myInstance = new ESRI_Factory();
    }
    return myInstance;
}


rjp_Shape * StaticFactory::createShape(QString fp)
{
    rjp_DatasetPtr temPtr(fp);
    int myType = temPtr.getValue()->shpHeader->nShapeType;
    switch(myType)
    {

    case 1:
    case 11:
    case 21:
    {
        return new rjp_Point(temPtr);
        break;
    }
    case 3:
    case 13:
    case 23:
    {
        return new rjp_Polyline(temPtr);
        break;
    }
    case 5:
    case 15:
    case 25:
    {
        return new rjp_Polygon(temPtr);
        break;
    }
    default:
    {
        return NULL;
        break;
    }

    }
}

rjp_Shape * ESRI_Factory::createShape(QString fp)
{
    return StaticFactory::createShape(fp);
}
