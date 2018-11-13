#include "rjp_shape.h"

#include "rjp_dataset.h"
#include "QPainter"

//rjp_Shape::rjp_Shape(rjp_DatasetPtr ds)
//{
//    DatasetPtr = ds;
//}

rjp_Shape* rjp_Shape::clone()
{
    rjp_DatasetPtr temDsp(DatasetPtr);
    int temSHPtype = temDsp.getValue()->shpHeader->nShapeType;
    switch(temSHPtype)
    {

    case 1:
    case 11:
    case 21:
    {
        return new rjp_Point(temDsp);
        break;
    }
    case 3:
    case 13:
    case 23:
    {
        return new rjp_Polyline(temDsp);
        break;
    }
    case 5:
    case 15:
    case 25:
    {
        return new rjp_Polygon(temDsp);
        break;
    }
    default:
    {
        return NULL;
        break;
    }

    }
}

double * rjp_Shape::date2Screen(double x, double y, QPaintDevice *pic, double *displayBox) const
{
    double picWidth = pic->width();
    double picHeight = pic->height();
    double xScale = 1.1*(displayBox[2] - displayBox[0])/picWidth;
    double yScale = 1.1*(displayBox[3] - displayBox[1])/picHeight;
    //为了保障所有图像都能画在pic上，所以选取比例大的
    double finalScale = xScale>yScale?xScale:yScale;
    //先将xmin,ymin整体平移到原点
    //由于之前的缩放是按照1.1缩放，所以再平移0.05才能保持居中
    x = x - displayBox[0] + (displayBox[2] - displayBox[0]) * 0.05;
    y = y - displayBox[1] + (displayBox[3] - displayBox[1]) * 0.05;
    //缩放到同一尺度
    x = x / finalScale;
    y = y / finalScale;
    //y值上下颠倒，即对于y = picheigh/2对阵
    y = picHeight - y;
    //根据不同情况，进步不同的平移
    if (xScale > yScale)
    {
        y = y - (picHeight/2 - 1.1*(displayBox[3]-displayBox[1])/(2*finalScale));
    }
    else
    {
        x = x + (picWidth/2 - 1.1*(displayBox[2] - displayBox[0])/(2*finalScale));
    }

    //该处会不会造成内存泄露?
    double * p = new double[2];
    p[0] = x;
    p[1] = y;
    return p;
}


rjp_DatasetPtr rjp_Shape::get_DatasetPtr()
{
    return DatasetPtr;
}

// need fixed
void rjp_Point::drawSHP(QPainter * painter, double *displayBox) const
{
    if(DatasetPtr.getValue()->isShown == false)
        return;

    //构建minbox和maxbox
    double display_minBox[4];
    double display_maxBox[4];

    display_minBox[0] = displayBox[0];
    display_minBox[1] = displayBox[1];
    display_minBox[2] = 0;display_minBox[3] = 0;

    display_maxBox[0] = displayBox[2];
    display_maxBox[1] = displayBox[3];
    display_maxBox[2] = 0;display_maxBox[3] = 0;

    //找到displaybox中的数据编号
    int * recordsHitIdList = NULL;
    int recordsHitCount = 0;
    recordsHitIdList = SHPTreeFindLikelyShapes(DatasetPtr.getValue()->searchTree,
                                               display_minBox,display_maxBox,
                                               &recordsHitCount);

    QPaintDevice * pic = painter->device();
    for(int i=0;i<recordsHitCount;i++)
    {
        SHPObject * shpContent = SHPReadObject(DatasetPtr.getValue()->shpHeader,recordsHitIdList[i]);
        double x = shpContent->padfX[0];
        double y = shpContent->padfY[0];
        double * temPair = date2Screen(x,y,pic,displayBox);
        x = temPair[0];
        y = temPair[1];
        painter->drawLine(QPointF(x-2,y),QPointF(x+2,y));
        painter->drawLine(QPointF(x,y-2),QPointF(x,y+2));

        //防止内存泄露
        delete temPair;
        temPair = NULL;
        SHPDestroyObject(shpContent);
        shpContent = NULL;
    }

    //防止内存泄露
    delete recordsHitIdList;
    recordsHitIdList = NULL;

}

void rjp_Polyline::drawSHP(QPainter * painter, double *displayBox) const
{
    if(DatasetPtr.getValue()->isShown == false)
        return;

    //构建minbox和maxbox
    double display_minBox[4];
    double display_maxBox[4];

    display_minBox[0] = displayBox[0];
    display_minBox[1] = displayBox[1];
    display_minBox[2] = 0;display_minBox[3] = 0;

    display_maxBox[0] = displayBox[2];
    display_maxBox[1] = displayBox[3];
    display_maxBox[2] = 0;display_maxBox[3] = 0;

    //找到displaybox中的数据编号
    int * recordsHitIdList = NULL;
    int recordsHitCount = 0;
    recordsHitIdList = SHPTreeFindLikelyShapes(DatasetPtr.getValue()->searchTree,
                                               display_minBox,display_maxBox,
                                               &recordsHitCount);

    QPaintDevice * pic = painter->device();

    for(int i=0;i<recordsHitCount;i++)
    {
        SHPObject * shpContent = SHPReadObject(DatasetPtr.getValue()->shpHeader,recordsHitIdList[i]);
        //重新构造parts数组
        QVector<int> newParts;
        for(int j=0;j<shpContent->nParts;j++)
        {
            newParts.append(shpContent->panPartStart[j]);
        }
        newParts.append(shpContent->nVertices);
        //开始绘图
        for(int j=0;j<newParts.size()-1;j++)
        {
            //由于点的个数比较多，所以使用vector效率比较低
            int pointCount = newParts[j+1] - newParts[j];
            QPointF * pointPair = new QPointF[pointCount];
            for(int k=newParts[j];k<newParts[j+1];k++)
            {
                double x = shpContent->padfX[k];
                double y = shpContent->padfY[k];
                double * temPoint = date2Screen(x,y,pic,displayBox);
                x = temPoint[0];
                y = temPoint[1];
                pointPair[k - newParts[j]].setX(x);
                pointPair[k - newParts[j]].setY(y);

                //防止内存泄露
                delete temPoint;
                temPoint = NULL;
            }
//
            painter->drawLines(pointPair,pointCount/2 - 1);

            //防止内存泄露
            delete pointPair;
            pointPair = NULL;
        }
        //防止内存泄露
        SHPDestroyObject(shpContent);
        shpContent = NULL;
    }
}

void rjp_Polygon::drawSHP(QPainter * painter, double *displayBox) const
{
    if(DatasetPtr.getValue()->isShown == false)
        return;

    //构建minbox和maxbox
    double display_minBox[4];
    double display_maxBox[4];

    display_minBox[0] = displayBox[0];
    display_minBox[1] = displayBox[1];
    display_minBox[2] = 0;display_minBox[3] = 0;

    display_maxBox[0] = displayBox[2];
    display_maxBox[1] = displayBox[3];
    display_maxBox[2] = 0;display_maxBox[3] = 0;

    //找到displaybox中的数据编号
    int * recordsHitIdList = NULL;
    int recordsHitCount = 0;
    recordsHitIdList = SHPTreeFindLikelyShapes(DatasetPtr.getValue()->searchTree,
                                               display_minBox,display_maxBox,
                                               &recordsHitCount);

    QPaintDevice * pic = painter->device();

    for(int i=0;i<recordsHitCount;i++)
    {
        SHPObject * shpContent = SHPReadObject(DatasetPtr.getValue()->shpHeader,recordsHitIdList[i]);

        //为了方便循环，重新构造parts
        QVector<int> newParts;
        for(int j=0;j<shpContent->nParts;j++)
        {
            newParts.append(shpContent->panPartStart[j]);
        }
        newParts.append(shpContent->nVertices);

        //开始绘图
        for(int j=0;j<newParts.size()-1;j++)
        {
            int pointCount = newParts[j+1] - newParts[j];
            QPointF * pointPairs = new QPointF[pointCount];

            for(int k= newParts[j];k<newParts[j+1];k++)
            {
                double x = shpContent->padfX[k];
                double y = shpContent->padfY[k];
                double * temPoint = date2Screen(x,y,pic,displayBox);
                x = temPoint[0];
                y = temPoint[1];
                pointPairs[k - newParts[j]].setX(x);
                pointPairs[k - newParts[j]].setY(y);
                //防止内存泄露
                delete temPoint;
                temPoint = NULL;
            }
            painter->drawPolygon(pointPairs,pointCount);

            delete pointPairs;
            pointPairs = NULL;

        }

        //防止内存泄露
        SHPDestroyObject(shpContent);
        shpContent = NULL;

    }
}
