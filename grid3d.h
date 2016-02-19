#ifndef GRID3D_H
#define GRID3D_H
#include "point3d.h"
#include "implicitobject.h"
#include <iostream>
#include <QVector>

using namespace std;

class Grid3D
{
public:
    Grid3D(Point3D* newOrigin, int newNumberX, int newNumberY, int newNumberZ, double newBarycentreDefaultUnkownedValue);
    //ecrit la sphere dans un fichier .mesh
    void writeMesh(string filepath, bool withGrid) const;
    //Affiche les coordonnées x, y, z
    void displayData() const;
    //Récupère le poids des nodes
    double getPropsForPoint(int x, int y, int z) const;
    //Surchage de la fonction précedante pour accéder aux informations par index
    double getPropsForPoint(int index) const;
    //Définis le poids des nodes
    void setPropsForPoint(int x, int y, int z, double value);
    //Surchage de la fonction précedante pour changer les informations par index
    void setPropsForPoint(int index, double value);
    void addImplicitObject(const ImplicitObject* s);

private:
    // Récupère l'index d'un node par ces coordonnées
    int getIndexFor(int x, int y, int z) const;
    // Variables qui permettent le calcule du barycentre
    Point3D* getBarycentreForPoint(Point3D* p1, double p1Value, Point3D* p2, double p2Value) const;
    string getBarycentreStringForPoint(Point3D* p1, double p1Value, Point3D* p2, double p2Value) const;

    //Liste et Poids des nodes
    QVector<double> nodePropsList;
    Point3D* origin;
    int numberX;
    int numberY;
    int numberZ;
    double barycentreDefaultUnkownedValue;
};

#endif // GRID3D_H
