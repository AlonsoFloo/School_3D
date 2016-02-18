#ifndef SURFACE3D_H
#define SURFACE3D_H
#include "triangle3d.h"
#include "node3d.h"
#include "point3d.h"
#include <QVector>

using namespace std;

class Surface3D
{
public:
    Surface3D(string filepath);
    //Affiche les différents résultats
    void displayData();
    //Ecrit un fichier mesh
    void writeMesh(string filepath);
    //Récupère le plus petit et le plus gros point
    Point3D* getMinPoint();
    Point3D* getMaxPoint();
    //Permet de calculer la normal
    Point3D* calculateNodeNormal(int indexNode);
    Point3D* calculateTriangleNormal(int indexTriangle);
    //Agrandit le model en multipliant par la normal et le ratio
    void bigUp(double ratio);

private:
    void parseFile(string filepath);
    double averageNodeCloseEachOther();
    double averageTriangleCloseEachOther();

    int nodesNumber;
    int shapeNumber;
    QVector<Node3D*> nodeList;
    QVector<Triangle3D*> triangleList;

};

#endif // SURFACE3D_H
