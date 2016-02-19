#include "sphere3d.h"
#include <iostream>
#include <cmath>

Sphere3D::Sphere3D(Point3D* newCenter, double newRad) : center(newCenter), rad(newRad)
{

}

double Sphere3D::getDistance(const Point3D* p) const {
    double distanceFromCenter = this->center->getDistanceTo(p);
    return distanceFromCenter - this->rad;
}
