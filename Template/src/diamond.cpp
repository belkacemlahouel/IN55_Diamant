#include "diamond.h"


Diamond::Diamond()
{

}

Diamond::Diamond(float pavillon, float crown, float rondiste, float table, float radius, float complexity, const GLfloat color[3], float alpha, float lvlPavillon, float lvlCrown)
{
    //complexity must be a multiple of 2
    if(fmod(complexity,2) != 0)
    {
        ++complexity;
    }

    Pavillon* pavillonDiamond = new Pavillon(radius, pavillon, lvlPavillon, complexity, color);
}

