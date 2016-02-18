#include "point3d.h"
#include <iostream>
#include <cmath>

Point3D::Point3D()
{

}

Point3D::Point3D(double newX, double newY, double newZ) : x(newX), y(newY), z(newZ)
{

}

Point3D* Point3D::crossProduct(Point3D* p1, Point3D* p2) {
    Point3D* p = new Point3D();
    p->x = p1->y * p2->z - p1->z  * p2->y;
    p->y = p1->z * p2->x - p1->x * p2->z;
    p->z = p1->x * p2->y - p1->y * p2->x;
    return p;
}

Point3D* Point3D::normalize() {
    double normal = std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    if (normal < 0.00000000001) {
        return new Point3D(0.,0.,0.);
    }
    Point3D *p = new Point3D();
    p->x = this->x / normal;
    p->y = this->y / normal;
    p->z = this->z / normal;
    return p;
}
