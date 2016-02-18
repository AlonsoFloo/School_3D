#ifndef NODE3D_H
#define NODE3D_H
#include "point3d.h"
#include <QVector>


class Node3D
{
public:
    Node3D();
    void appendUniqTriangleIndex(int index);
    void appendUniqPointIndex(int index);
    QVector<int> getTriangleIndexList();
    QVector<int> getPointIndexList();

    Point3D* point;
private:
    QVector<int> triangleIndexList;
    QVector<int> pointIndexList;
};

#endif // NODE3D_Hl
