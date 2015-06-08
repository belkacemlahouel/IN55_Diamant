#ifndef RONDISTE
#define RONDISTE

#include "Object3D.h"
#include "Types.h"
#include <iostream>
#include <math.h>

using namespace std;

class Rondiste : public Object3D
{
    private :
        GLfloat *verticesArray;
        GLushort *indicesArray;
        GLfloat *colorsArray;

        GLushort verticesArraySize;
        GLushort indicesArraySize;
        GLushort colorsArraySize;

        GLuint VertexVBOID;
        GLuint ColorVBOID;
        GLuint IndicesVBOID;

        bool  hasInitiatedVBO;

    public:
        Rondiste();
        Rondiste(float32 radius, float32 pavillonHeight, float32 rondisteHeight, int32 complexity, const GLfloat color[3]);
        ~Rondiste();

    protected :
        void initVBO();
        void drawShape(const char *shader_name);
        void computeNormals();
};

#endif // RONDISTE

