#ifndef PAVILLON_H
#define PAVILLON_H

#include "Object3D.h"
#include <math.h>

class Pavillon : public Object3D
{
    private :
        GLfloat *pavillonVertices;
        GLushort *pavillonIndices;
        GLfloat *colorsArray;

        GLushort verticesArraySize;
        GLushort indicesArraySize;

        GLuint VertexVBOID;
        GLuint ColorVBOID;
        GLuint IndicesVBOID;

        bool hasInitiatedVBO;

    public:
        Pavillon();
        Pavillon(float radius, float heigth, float heigthFirstLvl, int complexity, const GLfloat color[3]);
        ~Pavillon();

    protected:
        void initVBO();
        void drawShape(const char *shader_name);
};

#endif // PAVILLON_H
