#ifndef POINT3D_H
#define POINT3D_H


class Point3D
{
public:
    Point3D();
    Point3D(double newX, double newY, double newZ);
    double x;
    double y;
    double z;

    //Calcule la factorielle de 2 vecteurs
    static Point3D* crossProduct(Point3D* p1, Point3D* p2);
    Point3D* normalize() const;
    double getDistanceTo(const Point3D *p) const;
};

#endif // POINT3D_H
