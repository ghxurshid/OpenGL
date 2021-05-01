#ifndef XYZAXIS_H
#define XYZAXIS_H

#include "drawableobject.h"

class XYZAxis : public DrawableObject
{
public:
    XYZAxis(float length);
protected:
    void calculate() override;
};

#endif // XYZAXIS_H
