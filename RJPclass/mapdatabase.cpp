#include "mapdatabase.h"
#include "QVector"


flyWeightCity::flyWeightCity(QString n, QString i, QString p, double r):
    _name(n),
    _introduction(i),
    _province(p),
    _rainfall(r)
{}

QString flyWeightCity::getName()
{
    return _name;
}

flyWeightCity::~flyWeightCity()
{

}

flyWeightCityFactory::~flyWeightCityFactory()
{
    QVector<flyWeightCity*>::iterator itr;
    for(itr = _cities.begin();itr!= _cities.end();itr++)
    {
        delete * itr;
    }
    _cities.clear();

    // you can do the deletion in this way
    //if(_cities.size() != 0)
      //  _cities.clear();
}

flyWeightCity * flyWeightCityFactory::createCity(QString n, QString i, QString p, double r)
{
    QVector<flyWeightCity*>::iterator itr;

    for(itr = _cities.begin();itr!=_cities.end();itr++)
    {
        flyWeightCity * p = * itr;
        if(n == p->getName())
        {
            return p;
        }
    }
    flyWeightCity * pp = new flyWeightCity(n,i,p,r);
    _cities.append(pp);
    return pp;
}

MapRecord::MapRecord(flyWeightCity *c, int y):
    _city(c),
    year(y)
{}

MapRecord::~MapRecord()
{
    //Do not delete the Flyweight* city. It is used by all the objects.
    //Clean the memorey at the destruction function of FlyweightCityFactory
}
mapDatabase::mapDatabase()
{
    _factory = new flyWeightCityFactory();
}

mapDatabase::~mapDatabase()
{
    delete _factory;
}

void mapDatabase::addMapRecord(MapRecord *mr)
{
    _records.append(mr);
}


mapDatabase* mapDatabaseTest::dataBase = NULL;

void mapDatabaseTest::test()
{

    // no realizatioin
}
