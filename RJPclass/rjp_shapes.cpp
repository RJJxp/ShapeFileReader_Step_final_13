#include "rjp_shapes.h"

#include "QFileInfo"
#include "rjp_factory.h"

// initialize the static
rjp_Shapes * singletonShapes::gData = NULL;
// =============================================================================


rjp_Shapes::rjp_Shapes()
{
    displayBox = new double[4];
}

rjp_Shapes::rjp_Shapes(shapesObCommand *obc)
{
    obCommand = obc;
}
// a little bit useless, cause initializing, use get gData
//rjp_Shapes::rjp_Shapes(shapesObserver * ob)
//{
//    myOb = ob;
//    displayBox = new double[4];
//}

rjp_Shapes::rjp_Shapes(rjp_Shapes *temShapes)
{
    this->displayBox = new double[4];
    this->displayBox[0] = temShapes->get_dataBox()[0];
    this->displayBox[1] = temShapes->get_dataBox()[1];
    this->displayBox[2] = temShapes->get_dataBox()[2];
    this->displayBox[3] = temShapes->get_dataBox()[3];

    this->pathList = temShapes->get_pathList();

    for(int i=0;i<temShapes->getLayerSize();i++)
    {
        this->myLayers.append(temShapes->at(i)->clone());
    }

}

void rjp_Shapes::setObCommand(shapesObCommand *obs)
{
    obCommand = obs;
}

void rjp_Shapes::addShapes(QStringList fp)
{
    int oldPathlistLength = pathList.size();
    pathList.append(fp);
    for(int i=oldPathlistLength;i<pathList.size();i++)
    {
        QFileInfo fi(pathList[i]);
        if(!fi.isFile())
            continue;
        QString filePath = pathList[i];
        rjp_Shape * temShape = ESRI_Factory::getInstance()->createShape(filePath);
        myLayers.append(temShape);
    }

    // build the displaybox
    for(int i=0;i<myLayers.size();i++)
    {
        if(i==0)
        {
            displayBox[0] = myLayers[i]->get_DatasetPtr().getValue()->dataBox[0];
            displayBox[1] = myLayers[i]->get_DatasetPtr().getValue()->dataBox[1];
            displayBox[2] = myLayers[i]->get_DatasetPtr().getValue()->dataBox[2];
            displayBox[3] = myLayers[i]->get_DatasetPtr().getValue()->dataBox[3];
        }
        else
        {
            if(myLayers[i]->get_DatasetPtr().getValue()->dataBox[0] < displayBox[0])
            {
                displayBox[0] = myLayers[i]->get_DatasetPtr().getValue()->dataBox[0];
            }
            if(myLayers[i]->get_DatasetPtr().getValue()->dataBox[1] < displayBox[1])
            {
                displayBox[1] = myLayers[i]->get_DatasetPtr().getValue()->dataBox[1];
            }
            if(myLayers[i]->get_DatasetPtr().getValue()->dataBox[2] > displayBox[2])
            {
                displayBox[2] = myLayers[i]->get_DatasetPtr().getValue()->dataBox[2];
            }
            if(myLayers[i]->get_DatasetPtr().getValue()->dataBox[3] > displayBox[3])
            {
                displayBox[3] = myLayers[i]->get_DatasetPtr().getValue()->dataBox[3];
            }

        }
    }
}

void rjp_Shapes::drawAllShapes(QPainter *painter) const
{
    if(myLayers.size() == 0)
        return;
    for(int i=0;i<myLayers.size();i++)
    {
        painter->setPen(myLayers[i]->get_DatasetPtr().getValue()->paintColor);
        myLayers[i]->drawSHP(painter,displayBox);
    }
}

double * rjp_Shapes::get_dataBox()
{
    return displayBox;
}

QStringList rjp_Shapes::get_pathList()
{
    return pathList;
}

void rjp_Shapes::notify()
{
   //myOb->updateWhenShapesChange();
    obCommand->excute();
}

int rjp_Shapes::getLayerSize() const
{
    return myLayers.size();
}

rjp_Shapes::~rjp_Shapes()
{
    myLayers.clear();
}

//void rjp_Shapes::setOb(shapesObserver *ob)
//{
//    myOb=ob;
//}

rjp_Shape * rjp_Shapes::at(int i) const
{
    return myLayers[i];
}

rjp_Shapes * singletonShapes::get_gData()
{
    if(!gData)
    {
        gData = new rjp_Shapes();
    }
    return gData;
}

void singletonShapes::release_gData()
{
    if(gData)
        delete gData;
}
