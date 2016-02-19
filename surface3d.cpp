#include "surface3d.h"
#include <QFile>
#include <QTextStream>
#include <iostream>

Surface3D::Surface3D(string filepath)
{
    this->parseFile(filepath);
}


void Surface3D::parseFile(string filepath) {
    QString path = QString::fromStdString(filepath);
    QFile inputFile(path);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       int index = -1;
       int numberToIgnore = 4;
       bool isPoint = true;
       QString triangleStr = "Triangles";
       QString endStr = "End";
       bool isFirstLineFromPart = true;
       while (!in.atEnd())
       {
          ++index;
          QString line = in.readLine().trimmed();
          if (index < numberToIgnore || QString::compare(line, endStr, Qt::CaseInsensitive) == 0) {
            continue;
          }

          if (QString::compare(line, triangleStr, Qt::CaseInsensitive) == 0) {
              isPoint = false;
              isFirstLineFromPart = true;
              continue;
          }
          if (isPoint) {
            if (isFirstLineFromPart) {
                isFirstLineFromPart = false;
                this->nodesNumber = line.toInt();
            } else {
                Point3D* newPoint = new Point3D();
                QStringList pieces = line.split(" ");
                newPoint->x = pieces.at(0).toDouble();
                newPoint->y = pieces.at(1).toDouble();
                newPoint->z = pieces.at(2).toDouble();
                Node3D* newNode = new Node3D();
                newNode->point = newPoint;
                this->nodeList.append(newNode);
            }
          } else {
              if (isFirstLineFromPart) {
                  isFirstLineFromPart = false;
                  this->shapeNumber = line.toInt();
              } else {
                  Triangle3D* newTriangle = new Triangle3D();
                  QStringList pieces = line.split(" ");
                  newTriangle->indexP1 = pieces.at(0).toInt() - 1;
                  newTriangle->indexP2 = pieces.at(1).toInt() - 1;
                  newTriangle->indexP3 = pieces.at(2).toInt() - 1;
                  this->triangleList.append(newTriangle);
                  int triangleIndex = this->triangleList.length()-1;
                  this->nodeList.at(newTriangle->indexP1)->appendUniqTriangleIndex(triangleIndex);
                  this->nodeList.at(newTriangle->indexP2)->appendUniqTriangleIndex(triangleIndex);
                  this->nodeList.at(newTriangle->indexP3)->appendUniqTriangleIndex(triangleIndex);

                  this->nodeList.at(newTriangle->indexP1)->appendUniqPointIndex(newTriangle->indexP2);
                  this->nodeList.at(newTriangle->indexP1)->appendUniqPointIndex(newTriangle->indexP3);

                  this->nodeList.at(newTriangle->indexP2)->appendUniqPointIndex(newTriangle->indexP1);
                  this->nodeList.at(newTriangle->indexP2)->appendUniqPointIndex(newTriangle->indexP3);

                  this->nodeList.at(newTriangle->indexP3)->appendUniqPointIndex(newTriangle->indexP1);
                  this->nodeList.at(newTriangle->indexP3)->appendUniqPointIndex(newTriangle->indexP2);
              }
          }
       }
       inputFile.close();
    }
}

void Surface3D::displayData() const {
    cout << "Point number : " << this->nodesNumber << endl;
    cout << "Shapes number : " << this->shapeNumber << endl;
    Point3D *p = this->getMaxPoint();
    cout << "Max Point : " << p->x << " " << p->y << " " << p->z << endl;
    Point3D *p2 = this->getMinPoint();
    cout << "Min Point : " << p2->x << " " << p2->y << " " << p2->z << endl;
    Point3D *normal0 = this->calculateNodeNormal(0);
    cout << "Normal Point 0 : " << normal0->x << " " << normal0->y << " " << normal0->z << endl;
    normal0 = this->calculateNodeNormal(0)->normalize();
    cout << "Normal Point 0 Normalized : " << normal0->x << " " << normal0->y << " " << normal0->z << endl;
    double avg = this->averageNodeCloseEachOther();
    cout << "Average node close each other : " << avg << endl;
    avg = this->averageTriangleCloseEachOther();
    cout << "Average triangle close each other : " << avg << endl;
    cout << endl<< endl<< endl;
}

void Surface3D::writeMesh(string filepath) const {
    QString filename = QString::fromStdString(filepath);
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite|QIODevice::Truncate) )
    {
        QTextStream stream( &file );
        stream << "MeshVersionFormatted 1" << endl;
        stream << "Dimension" << endl;
        stream << "3" << endl;
        stream << "Vertices" << endl;
        stream << this->nodesNumber << endl;
        for(int i = 0; i < this->nodeList.length(); ++i) {
            Point3D* p = this->nodeList.at(i)->point;
            stream << p->x <<  " " << p->y << " " << p->z << " 0" <<  endl;
        }
        stream << "Triangles" << endl;
        stream << this->shapeNumber << endl;
        for(int i = 0; i < this->triangleList.length(); ++i) {
            Triangle3D* t = this->triangleList.at(i);
            stream << t->indexP1 + 1 <<  " " << t->indexP2 + 1 << " " << t->indexP3 + 1 << " 508" <<  endl;
        }
        stream << "End" << endl;
        file.close();
    }
}

Point3D* Surface3D::getMinPoint() const {
    double minX = 0;
    double minY = 0;
    double minZ = 0;
    bool isFirst = true;
    for(int i = 0; i < this->nodeList.length(); ++i) {
        Point3D* p = this->nodeList.at(i)->point;
        if (isFirst || p->x < minX) {
            minX = p->x;
        }
        if (isFirst || p->y < minY) {
            minY = p->y;
        }
        if (isFirst || p->z < minZ) {
            minZ = p->z;
        }
        isFirst = false;
    }
    Point3D* p =  new Point3D();
    p->x = minX;
    p->y = minY;
    p->z = minZ;
    return p;
}

Point3D* Surface3D::getMaxPoint() const {
    double maxX = 0;
    double maxY = 0;
    double maxZ = 0;
    bool isFirst = true;
    for(int i = 0; i < this->nodeList.length(); ++i) {
        Point3D* p = this->nodeList.at(i)->point;
        if (isFirst || p->x > maxX) {
            maxX = p->x;
        }
        if (isFirst || p->y > maxY) {
            maxY = p->y;
        }
        if (isFirst || p->z > maxZ) {
            maxZ = p->z;
        }
        isFirst = false;
    }
    Point3D* p =  new Point3D();
    p->x = maxX;
    p->y = maxY;
    p->z = maxZ;
    return p;
}


Point3D* Surface3D::calculateNodeNormal(int indexNode) const {
    Point3D *sumVector = new Point3D();
    sumVector->x = 0;
    sumVector->y = 0;
    sumVector->z = 0;
    Node3D* node = this->nodeList.at(indexNode);
    int numberFound = node->getTriangleIndexList().length();
    for(int i = 0; i < numberFound; i++) {
        int triangleIndex = node->getTriangleIndexList().at(i);
        Point3D* normalTriangle = this->calculateTriangleNormal(triangleIndex);
        sumVector->x += normalTriangle->x;
        sumVector->y += normalTriangle->y;
        sumVector->z += normalTriangle->z;
    }
    if (numberFound == 0) {
        return new Point3D(0.,0.,0.);
    }
    sumVector->x *= 1./ (double)numberFound;
    sumVector->y *= 1./ (double)numberFound;
    sumVector->z *= 1./ (double)numberFound;
    return sumVector;
}

Point3D* Surface3D::calculateTriangleNormal(int indexTriangle) const {
    Triangle3D* t = this->triangleList.at(indexTriangle);
    Point3D* p1 = this->nodeList.at(t->indexP1)->point;
    Point3D* p2 = this->nodeList.at(t->indexP2)->point;
    Point3D* p3 = this->nodeList.at(t->indexP3)->point;

    Point3D* p1p2 = new Point3D();
    p1p2->x = p2->x - p1->x;
    p1p2->y = p2->y - p1->y;
    p1p2->z = p2->z - p1->z;
    Point3D* p1p3 = new Point3D();
    p1p3->x = p3->x - p1->x;
    p1p3->y = p3->y - p1->y;
    p1p3->z = p3->z - p1->z;
    return Point3D::crossProduct(p1p2, p1p3);
}

void Surface3D::bigUp(double ratio) {
    for(int i = 0; i < this->nodeList.length(); ++i) {
        Point3D* p = this->nodeList.at(i)->point;
        Point3D* normal = this->calculateNodeNormal(i)->normalize();
        p->x += ratio * normal->x;
        p->y += ratio * normal->y;
        p->z += ratio * normal->z;
    }
}

double Surface3D::averageNodeCloseEachOther() const {
    double value = 0.;
    for (int i = 0; i < this->nodeList.length(); ++i) {
        Node3D *n = this->nodeList.at(i);
        value += n->getPointIndexList().length();
    }
    return value / this->nodeList.length();
}

double Surface3D::averageTriangleCloseEachOther() const {
    double value = 0.;
    for (int i = 0; i < this->nodeList.length(); ++i) {
        Node3D *n = this->nodeList.at(i);
        value += n->getTriangleIndexList().length();
    }
    return value / this->nodeList.length();
}
