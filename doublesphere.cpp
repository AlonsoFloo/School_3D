#include "doublesphere.h"

DoubleSphere::DoubleSphere(Sphere3D* newS1, Sphere3D* newS2) : s1(newS1), s2(newS2) {

}

double DoubleSphere::getDistance(const Point3D* p){
    double d1 = this->s1->getDistance(p);
    double d2 = this->s2->getDistance(p);
    return d1 > d2 ? d2 : d1;
}
