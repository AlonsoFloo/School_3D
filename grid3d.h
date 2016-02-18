#ifndef GRID3D_H
#define GRID3D_H
#include "point3d.h"
#include "implicitobject.h"
#include <iostream>
#include <QVector>

using namespace std;

class Grid3D
{
public:
    Grid3D(Point3D* newOrigin, int newNumberX, int newNumberY, int newNumberZ);
    void writeMesh(string filepath, bool withGrid);
    void displayData();
    double getPropsForPoint(int x, int y, int z);
    double getPropsForPoint(int index);
    void setPropsForPoint(int x, int y, int z, double value);
    void setPropsForPoint(int index, double value);
    void addImplicitObject(ImplicitObject* s);

private:
    int getIndexFor(int x, int y, int z);
    Point3D* getBarycentreForPoint(Point3D* p1, double p1Value, Point3D* p2, double p2Value);
    string getBarycentreStringForPoint(Point3D* p1, double p1Value, Point3D* p2, double p2Value);

    QVector<double> nodePropsList;
    Point3D* origin;
    int numberX;
    int numberY;
    int numberZ;
};

#endif // GRID3D_H
