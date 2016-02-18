#include "node3d.h"

Node3D::Node3D()
{

}

void Node3D::appendUniqTriangleIndex(int index) {
    bool valueFound = this->triangleIndexList.indexOf(index) > -1;
    if (!valueFound) {
        this->triangleIndexList.append(index);
    }
}

void Node3D::appendUniqPointIndex(int index) {
    bool valueFound = this->pointIndexList.indexOf(index) > -1;
    if (!valueFound) {
        this->pointIndexList.append(index);
    }
}

QVector<int> Node3D::getTriangleIndexList() {
    return this->triangleIndexList;
}

QVector<int> Node3D::getPointIndexList() {
    return this->pointIndexList;
}
