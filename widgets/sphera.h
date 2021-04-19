#ifndef SPHERA_H
#define SPHERA_H

#include "drawableobject.h"

class Sphera : public DrawableObject
{
public:
    Sphera(double radius = 1, QVector3D position = QVector3D(0, 0, 0));
};

#endif // SPHERA_H
