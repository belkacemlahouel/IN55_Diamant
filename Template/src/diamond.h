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
    private:
        Pavillon* pavillon;

    public:
        Diamond();
        Diamond(float32 pavillon, float32 crown, float32 rondiste, float32 table, float32 radius, int32 complexity, const GLfloat color[3], float32 alpha, float32 lvlPavillon, float32 lvlCrown);
        ~Diamond();
};

#endif // DIAMOND_H
