#ifndef MATERIAL
#define MATERIAL

#include "Color.h"
#include "Types.h"

class Material
{
    public:
        GLfloat *ambient;
        GLfloat *diffuse;
        GLfloat *specular;
        GLfloat shininess;

        Material(GLfloat ambient[4], GLfloat diffuse[4], GLfloat specular[4], GLfloat shininess);
};

#endif // MATERIAL

