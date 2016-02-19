#ifndef DOUBLESPHERE_H
#define DOUBLESPHERE_H
#include "sphere3d.h"

class DoubleSphere : public ImplicitObject
{
public:
    DoubleSphere(Sphere3D* newS1, Sphere3D* newS2);
    double getDistance(const Point3D* p) const;

private:
    Sphere3D* s1;
    Sphere3D* s2;
};

#endif // DOUBLESPHERE_H
