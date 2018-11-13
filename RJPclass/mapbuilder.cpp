#include "mapbuilder.h"
#include "rjp_shapes.h"

void  mapBuilder::buildShapes(rjp_Shapes * temShapes)
{
    if(_map->_shapes)
        delete _map->_shapes;

    _map->_shapes = new rjp_Shapes(temShapes);

}
