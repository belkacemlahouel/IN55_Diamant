#ifndef DIAMOND_H
#define DIAMOND_H

#include "Color.h"
#include "Types.h"
#include "Object3D.h"
#include "BasicObjects/pavillon.h"
#include "BasicObjects/rondiste.h"
#include "BasicObjects/table.h"
#include "BasicObjects/crown.h"
#include <iostream>
#include <cmath>

/**
 * @brief The Diamond class
 * Create and draw a diamond with different parameters.
 * @param pavillon is the height of the "pavillon" of the diamond.
 * @param crown is the height of the crown of the diamond.
 * @param rondiste is the height of the "rondiste" of the diamond.
 * @param table is the size of the table of the diamond.
 * @param radius is its radius.
 * @param complexity is the number of triangles in the "rondiste" (its change all the complexity of the diamond).
 * @param color is its color.
 * @param alpha is the transparancy/purity of the diamond.
 * @param lvlPavillon, the height of the first level of points in the "pavillon".
 * @param lvlCrown, the height of the first level of points in the crown.
 */
class Diamond : public Object3D
{
    private:
        Pavillon* pavillon;
        Rondiste* rondiste;
        Crown* crown;
        Table* table;

    public:
        Diamond();
        Diamond(float32 pavillon, float32 crown, float32 rondiste, float32 table, float32 radius, int32 complexity, const GLfloat color[3], float32 alpha, float32 lvlPavillon, float32 lvlCrown);
        ~Diamond();
        void drawShape(const char *shader_name);
};

#endif // DIAMOND_H
