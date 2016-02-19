#include "pointlist.h"

PointList::PointList(QVector<Point3D*> newPointList) : pointList(newPointList)
{

}

double PointList::getDistance(const Point3D* p) {
    double minValue = -1;
    bool isFirst = true;
    for (int i = 0; i < pointList.length(); ++i) {
        double d = pointList.at(i)->getDistanceTo(p);
        if (isFirst || d < minValue) {
            minValue = d;
        }
        isFirst = false;
    }
    return minValue;
}
