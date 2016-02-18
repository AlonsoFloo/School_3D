#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include "surface3d.h"
#include "grid3d.h"
#include "sphere3d.h"
#include "doublesphere.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    string filepath = "C:\\Users\\Maxime\\Desktop\\Model_3D\\MAILLAGE\\bunny.mesh";

    Surface3D surface(filepath);
    surface.displayData();

    string filepathTmp = "C:\\Users\\Maxime\\Desktop\\Model_3D\\MAILLAGE\\tmp_rewrite.mesh";
    surface.writeMesh(filepathTmp);
    surface.displayData();

    surface.bigUp(0.01);
    filepathTmp = "C:\\Users\\Maxime\\Desktop\\Model_3D\\MAILLAGE\\tmp_big.mesh";
    surface.writeMesh(filepathTmp);
    surface.displayData();

    Point3D* originGrid = new Point3D(0., 0., 0.);

    Grid3D grid(originGrid, 4, 4, 4);
    filepathTmp = "C:\\Users\\Maxime\\Desktop\\Model_3D\\MAILLAGE\\tmp_grid.mesh";
    grid.writeMesh(filepathTmp, true);
    grid.displayData();

    Point3D* originSphere = new Point3D(50., 50., 50.);
    Grid3D grid2(originGrid, 100, 100, 100);
    Sphere3D sphere(originSphere, 40);
    grid2.addImplicitObject(&sphere);
    filepathTmp = "C:\\Users\\Maxime\\Desktop\\Model_3D\\MAILLAGE\\tmp_sphere_implicite.mesh";
    grid2.writeMesh(filepathTmp, false);

    Grid3D grid3(originGrid, 100, 100, 100);
    originSphere = new Point3D(30., 30., 30.);
    Sphere3D* sphere1 = new Sphere3D(originSphere, 30);
    originSphere = new Point3D(60., 60., 60.);
    Sphere3D* sphere2 = new Sphere3D(originSphere, 30);
    DoubleSphere doubleSphere(sphere1, sphere2);
    grid3.addImplicitObject(&doubleSphere);
    filepathTmp = "C:\\Users\\Maxime\\Desktop\\Model_3D\\MAILLAGE\\tmp_double_sphere_implicite.mesh";
    grid3.writeMesh(filepathTmp, false);

    std::cout << "END";

    system(filepathTmp.c_str());

    return a.exec();
}
