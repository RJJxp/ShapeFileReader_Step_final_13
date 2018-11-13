#ifndef RJP_DATASET_H
#define RJP_DATASET_H

#include "shapelib/shapefil.h"
#include "QString"
#include "QColor"
#include "string"

class rjp_Dataset
{
public:
    rjp_Dataset(QString filePath);
    ~rjp_Dataset();

    // source data, once initialized, fixed
    QString myName;
    bool isShown;
    SHPHandle shpHeader;
    SHPTree * searchTree;
    double * dataBox;
    QColor paintColor;

    // to count the reference times
    int refCount;
};

// using smart pointer to represent the dataset
class rjp_DatasetPtr
{
public:
    // service for 3rd intializing function
    rjp_Dataset * getValue() const;
    // 3 initializing overload functions
    rjp_DatasetPtr(QString filePath);
    rjp_DatasetPtr(rjp_Dataset * headerValue);
    rjp_DatasetPtr(const rjp_DatasetPtr& rhs);// right hand side
    // overload of the string =
    rjp_DatasetPtr& operator = (const rjp_DatasetPtr& rhs);
    // destructor function
    ~rjp_DatasetPtr();

    // former shape public function
    // in fact we don't need these, cause all the parameter's definition is public

    /*
    double * get_DataBox() const {return dataBox;}
    QString get_Name() const {return myName;}
    QColor get_PaintColor() const {return paintColor;}
    bool get_isShow() const {return isShown;}
    SHPHandle get_shpHeader() const {return shpHeader;}
    SHPTree * get_searchTree() const {return searchTree;}
    */

private:
    rjp_Dataset * value;

};
#endif // RJP_DATASET_H
