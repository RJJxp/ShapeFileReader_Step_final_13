#include "rjp_dataset.h"

#include "shapelib/shapefil.h"
#include "QFileInfo"

rjp_Dataset::rjp_Dataset(QString filePath)
{
    // most important part
    refCount = 1;
    // set header and tree
    shpHeader = SHPOpen(filePath.toStdString().c_str(), "rb+");
    searchTree = SHPCreateTree(shpHeader,2,10,NULL,NULL);
    SHPTreeTrimExtraNodes(searchTree);
    // set name
    QFileInfo fi(filePath);
    myName = fi.baseName();
    // set databox isShow color
    dataBox = new double[4];
    dataBox[0] = shpHeader->adBoundsMin[0];
    dataBox[1] = shpHeader->adBoundsMin[1];
    dataBox[2] = shpHeader->adBoundsMax[0];
    dataBox[3] = shpHeader->adBoundsMax[1];
    isShown = true;
    paintColor.setRgb(qrand()%255,qrand()%255,qrand()%255);
}

rjp_Dataset::~rjp_Dataset()
{

}

rjp_DatasetPtr::~rjp_DatasetPtr()
{

}

// 4 function involves intializing
rjp_Dataset * rjp_DatasetPtr::getValue() const
{
    return value;
}

rjp_DatasetPtr::rjp_DatasetPtr(const rjp_DatasetPtr &rhs)
{
    value = rhs.getValue();
    value->refCount++;// ref + 1
}

rjp_DatasetPtr::rjp_DatasetPtr(QString filePath)
{
    value = new rjp_Dataset(filePath);
}

rjp_DatasetPtr::rjp_DatasetPtr(rjp_Dataset *headerValue)
{
    value = headerValue;
}

// overload of the =
rjp_DatasetPtr& rjp_DatasetPtr::operator =(const rjp_DatasetPtr& rhs)
{
    // guess this means an address
    if(this == &rhs)
        return * this;

    if(--value->refCount == 0)
        delete value;

    value = rhs.getValue();
    ++value->refCount;

    return * this;
}
