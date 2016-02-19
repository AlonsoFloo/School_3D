#ifndef SPHERE3D_H
#define SPHERE3D_H
#include "point3d.h"
#include "implicitobject.h"

class Sphere3D : public ImplicitObject
{
public:
    Sphere3D(Point3D* newCenter, double newRad);
    double getDistance(const Point3D* p) const;

private:
    Point3D* center;
    double rad;
};

#endif // SPHERE3D_H
