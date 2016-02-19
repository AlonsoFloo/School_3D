#ifndef IMPLICITOBJECT_H
#define IMPLICITOBJECT_H
#include "point3d.h"

class ImplicitObject
{
public:
    virtual double getDistance(const Point3D* p) const = 0;
};

#endif // IMPLICITOBJECT_H
