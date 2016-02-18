#include "sphere3d.h"
#include <iostream>
#include <cmath>

Sphere3D::Sphere3D(Point3D* newCenter, double newRad) : center(newCenter), rad(newRad)
{

}

double Sphere3D::getDistance(const Point3D* p) {
    double distanceFromCenter = (std::sqrt(pow(this->center->x - p->x, 2) +  pow(this->center->y - p->y, 2) + pow(this->center->z - p->z, 2)));
    return distanceFromCenter - this->rad;
}
