#ifndef POINTLIST_H
#define POINTLIST_H
#include "implicitobject.h"
#include "point3d.h"
#include <QVector>


class PointList : public ImplicitObject
{
public:
    PointList(QVector<Point3D*> newPointList);
    double getDistance(const Point3D* p) const;

private:
    QVector<Point3D*> pointList;
};

#endif // POINTLIST_H
