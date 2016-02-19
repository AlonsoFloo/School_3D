#include "grid3d.h"
#include <QString>
#include <QFile>
#include <QTextStream>

Grid3D::Grid3D(Point3D* newOrigin, int newNumberX, int newNumberY, int newNumberZ, double newBarycentreDefaultUnkownedValue) : origin(newOrigin), numberX(newNumberX), numberY(newNumberY), numberZ(newNumberZ), barycentreDefaultUnkownedValue(newBarycentreDefaultUnkownedValue)
{
    for(int indexZ = 0; indexZ < this->numberZ + 1; ++indexZ) {
        for(int indexY = 0; indexY < this->numberY + 1; ++indexY) {
            for(int indexX = 0; indexX < this->numberX + 1; ++indexX) {
                this->nodePropsList.append(1.);
            }
        }
    }
}


void Grid3D::writeMesh(string filepath, bool withGrid) const {
    QString filename = QString::fromStdString(filepath);
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite|QIODevice::Truncate) )
    {
        QTextStream stream( &file);

        QVector<string> pointList;
        for(int indexZ = 0; indexZ < this->numberZ + 1; ++indexZ) {
            for(int indexY = 0; indexY < this->numberY + 1; ++indexY) {
                for(int indexX = 0; indexX < this->numberX + 1; ++indexX) {
                    if (withGrid) {
                        pointList.append(std::to_string(this->origin->x + indexX) + " " + std::to_string(this->origin->y + indexY) + " " + std::to_string(this->origin->z + indexZ) + " 0");
                    }
                }
            }
        }

        QVector<string> hexaheraList;
        for(int indexZ = 0; indexZ < this->numberZ; ++indexZ) {
            for(int indexY = 0; indexY < this->numberY; ++indexY) {
                for(int indexX = 0; indexX < this->numberX; ++indexX) {
                    Point3D* p = new Point3D(indexX, indexY, indexZ);
                    int p1 = this->getIndexFor(p->x, p->y, p->z);
                    int p2 = this->getIndexFor(p->x+1, p->y, p->z);
                    int p3 = this->getIndexFor(p->x+1, p->y+1, p->z);
                    int p4 = this->getIndexFor(p->x, p->y+1, p->z);
                    int p5 = this->getIndexFor(p->x, p->y, p->z+1);
                    int p6 = this->getIndexFor(p->x+1, p->y, p->z+1);
                    int p7 = this->getIndexFor(p->x+1, p->y+1, p->z+1);
                    int p8 = this->getIndexFor(p->x, p->y+1, p->z+1);
                    if (withGrid) {
                        hexaheraList.append(std::to_string(p1 + 1) + " " + std::to_string(p2 + 1) + " " + std::to_string(p3 + 1) + " " + std::to_string(p4 + 1) + " " + std::to_string(p5 + 1) + " " + std::to_string(p6 + 1) + " " + std::to_string(p7 + 1) + " " + std::to_string(p8 + 1)+ " 508");
                    }

                    Point3D *p13D = new Point3D(this->origin->x + p->x, this->origin->y + p->y, this->origin->z + p->z);
                    Point3D *p23D = new Point3D(this->origin->x + p->x+1, this->origin->y + p->y, this->origin->z + p->z);
                    Point3D *p33D = new Point3D(this->origin->x + p->x+1, this->origin->y + p->y+1, this->origin->z + p->z);
                    Point3D *p43D = new Point3D(this->origin->x + p->x, this->origin->y + p->y+1, this->origin->z + p->z);
                    Point3D *p53D = new Point3D(this->origin->x + p->x, this->origin->y + p->y, this->origin->z + p->z+1);
                    Point3D *p63D = new Point3D(this->origin->x + p->x+1, this->origin->y + p->y, this->origin->z + p->z+1);
                    Point3D *p73D = new Point3D(this->origin->x + p->x+1, this->origin->y + p->y+1, this->origin->z + p->z+1);
                    Point3D *p83D = new Point3D(this->origin->x + p->x, this->origin->y + p->y+1, this->origin->z + p->z+1);

                    string value = this->getBarycentreStringForPoint(p13D, this->getPropsForPoint(p1), p23D, this->getPropsForPoint(p2));
                    if (value != "") pointList.append(value);
                    value = this->getBarycentreStringForPoint(p23D, this->getPropsForPoint(p2), p33D, this->getPropsForPoint(p3));
                    if (value != "") pointList.append(value);
                    value = this->getBarycentreStringForPoint(p33D, this->getPropsForPoint(p3), p43D, this->getPropsForPoint(p4));
                    if (value != "") pointList.append(value);
                    value = this->getBarycentreStringForPoint(p43D, this->getPropsForPoint(p4), p13D, this->getPropsForPoint(p1));
                    if (value != "") pointList.append(value);
                    value = this->getBarycentreStringForPoint(p53D, this->getPropsForPoint(p5), p63D, this->getPropsForPoint(p6));
                    if (value != "") pointList.append(value);
                    value = this->getBarycentreStringForPoint(p63D, this->getPropsForPoint(p6), p73D, this->getPropsForPoint(p7));
                    if (value != "") pointList.append(value);
                    value = this->getBarycentreStringForPoint(p73D, this->getPropsForPoint(p7), p83D, this->getPropsForPoint(p8));
                    if (value != "") pointList.append(value);
                    value = this->getBarycentreStringForPoint(p83D, this->getPropsForPoint(p8), p53D, this->getPropsForPoint(p5));
                    if (value != "") pointList.append(value);
                    value = this->getBarycentreStringForPoint(p13D, this->getPropsForPoint(p1), p53D, this->getPropsForPoint(p5));
                    if (value != "") pointList.append(value);
                    value = this->getBarycentreStringForPoint(p23D, this->getPropsForPoint(p2), p63D, this->getPropsForPoint(p6));
                    if (value != "") pointList.append(value);
                    value = this->getBarycentreStringForPoint(p33D, this->getPropsForPoint(p3), p73D, this->getPropsForPoint(p7));
                    if (value != "") pointList.append(value);
                    value = this->getBarycentreStringForPoint(p43D, this->getPropsForPoint(p4), p83D, this->getPropsForPoint(p8));
                    if (value != "") pointList.append(value);
                }
            }
        }

        stream << "MeshVersionFormatted 1" << endl;
        stream << "Dimension" << endl;
        stream << "3" << endl;
        stream << "Vertices" << endl;
        stream << pointList.length() << endl;
        for (int i = 0; i < pointList.length(); ++i) {
            stream << QString::fromStdString(pointList.at(i)) <<  endl;
        }

        stream << "Hexahedra" << endl;
        stream << hexaheraList.length() << endl;
        for (int i = 0; i < hexaheraList.length(); ++i) {
            stream << QString::fromStdString(hexaheraList.at(i)) <<  endl;
        }


        stream << "End" << endl;
        file.close();
    }
}

Point3D* Grid3D::getBarycentreForPoint(Point3D* p1, double p1Value, Point3D* p2, double p2Value) const {
    if ((p1Value > barycentreDefaultUnkownedValue && p2Value > barycentreDefaultUnkownedValue)
            || (p1Value < barycentreDefaultUnkownedValue && p2Value < barycentreDefaultUnkownedValue)
            || (p1Value - p2Value == 0)) {
        return nullptr;
    }
    double t =  1 - ((p1Value - barycentreDefaultUnkownedValue) / (p1Value - p2Value));
    return new Point3D(t*p1->x + (1-t)*p2->x, t*p1->y + (1-t)*p2->y, t*p1->z + (1-t)*p2->z);
}

string Grid3D::getBarycentreStringForPoint(Point3D* p1, double p1Value, Point3D* p2, double p2Value) const {
    Point3D *b = this->getBarycentreForPoint(p1, p1Value, p2, p2Value);
    if (b != nullptr) {
        return std::to_string(b->x) + " " + std::to_string(b->y) + " " + std::to_string(b->z) + " 0";
    }
    return "";
}

void Grid3D::displayData() const {
    cout << "Origin point : " << this->origin->x << " " << this->origin->y << " " << this->origin->z << endl;
    cout << "Number on X : " << this->numberX << endl;
    cout << "Number on Y : " << this->numberY << endl;
    cout << "Number on Z : " << this->numberZ << endl;
    cout << "Props :  [";
    for (int i = 0; i < this->nodePropsList.length(); ++i) {
        if (i > 0) {
            cout << ", ";
        }
        cout << this->nodePropsList.at(i);
    }
    cout << "]" << endl;

    cout << endl<< endl<< endl;
}

int Grid3D::getIndexFor(int x, int y, int z) const {
    return x + (this->numberX + 1) * y + (this->numberX + 1) * (this->numberY + 1) * z;
}

double Grid3D::getPropsForPoint(int x, int y, int z) const {
    int index = this->getIndexFor(x, y, z);
    return this->getPropsForPoint(index);
}

double Grid3D::getPropsForPoint(int index) const {
    return this->nodePropsList.at(index);
}

void Grid3D::setPropsForPoint(int x, int y, int z, double value) {
    int index = this->getIndexFor(x, y, z);
    this->setPropsForPoint(index, value);

}

void Grid3D::setPropsForPoint(int index, double value) {
    this->nodePropsList.replace(index, value);

}

void Grid3D::addImplicitObject(const ImplicitObject* s) {
    for(int indexZ = 0; indexZ < numberZ + 1; ++indexZ) {
        for(int indexY = 0; indexY < numberY + 1; ++indexY) {
            for(int indexX = 0; indexX < numberX + 1; ++indexX) {
                Point3D* point = new Point3D(this->origin->x + indexX, this->origin->y + indexY, this->origin->z + indexZ);
                double distance = s->getDistance(point);
                this->setPropsForPoint(indexX, indexY, indexZ, distance);
            }
        }
    }
}
