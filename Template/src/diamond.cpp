#include "diamond.h"


Diamond::Diamond()
{

}

Diamond::Diamond(float32 pavillon, float32 crown, float32 rondiste, float32 table, float32 radius, int32 complexity, const GLfloat color[3], float32 alpha, float32 lvlPavillon, float32 lvlCrown)
{
    //complexity must be a multiple of 2
    if(fmod(complexity,2) != 0)
    {
        ++complexity;
    }

    this->pavillon = new Pavillon(radius, pavillon, lvlPavillon, complexity, rondiste, color);
}
Diamond::~Diamond()
{
    delete this->pavillon;
    delete this->rondiste;
}
