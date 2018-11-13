#ifndef MAPDATABASE_H
#define MAPDATABASE_H

#include "QString"
#include "rjp_shapes.h"

class flyWeightCity
{
public:
    flyWeightCity(QString n,QString i,QString p,double r);
    ~flyWeightCity();

    QString getName();
private:
    QString _name;
    QString _introduction;
    QString _province;
    double _rainfall;
};

class flyWeightCityFactory
{
public:
    ~flyWeightCityFactory();
    flyWeightCity * createCity(QString n,QString i,QString p,double r);
private:
    QVector<flyWeightCity*> _cities;
};

class MapRecord
{
public:
    MapRecord(flyWeightCity * c,int y);
    ~MapRecord();
private:
    flyWeightCity * _city;
    int year;
    rjp_Shapes * _shapes;
};


class mapDatabase
{
public:
    mapDatabase();
    ~mapDatabase();
    void addMapRecord(MapRecord * mr);
    void listAllRecords(){}
    flyWeightCityFactory * getFactory(){return _factory;}
private:
    QVector<MapRecord *> _records;
    flyWeightCityFactory * _factory;
};

class mapDatabaseTest
{
public:
    static void test();
private:
    static mapDatabase * dataBase;
};





#endif // MAPDATABASE_H
