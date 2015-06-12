#ifndef MATERIAL
#define MATERIAL

#include "Color.h"
#include "Types.h"

class Material
{
    private:
        GLfloat *ambient;
        GLfloat *diffuse;
        GLfloat *specular;
        GLfloat shininess;

        AbstractFramework* m_Framework = NULL;

    public:

        Material(AbstractFramework* fw, GLfloat ambient[4], GLfloat diffuse[4], GLfloat specular[4], GLfloat shininess);

        void submitMaterial();
};

#endif // MATERIAL

