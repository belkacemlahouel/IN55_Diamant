#ifndef DIAMOND_H
#define DIAMOND_H

#include "Color.h"
#include "Types.h"
#include "Object3D.h"
#include "BasicObjects/pavillon.h"
#include <iostream>
#include <cmath>

class Diamond : public Object3D
{
    public:
        Diamond();
        Diamond(float pavillon, float crown, float rondiste, float table, float radius, float complexity, const GLfloat color[3], float alpha, float lvlPavillon, float lvlCrown);
};

#endif // DIAMOND_H
