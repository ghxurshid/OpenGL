#ifndef SPHERA_H
#define SPHERA_H

#include "drawableobject.h"

class Sphera : public DrawableObject
{
public:     
    Sphera(double radius = 1, int arc = 360, int highLat = 90,
           int lowLat = -90, QQuaternion rotation = QQuaternion(),
           QVector3D position = QVector3D(0, 0, 0), QVector3D scalar = QVector3D(1.0f, 1.0f, 1.0f));
    ~Sphera() override;
private:
    int m_arc;
    double m_radius;
    int m_highLatitude;
    int m_lowLatitude;

    void calculate() override;
    VertexData calcVertex(int longitude, int latidude);
};

#endif // SPHERA_H
