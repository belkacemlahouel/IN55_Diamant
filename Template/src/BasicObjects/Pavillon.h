#ifndef PAVILLON_H
#define PAVILLON_H

#include "BasicObjects/pavillon.h"
#include "Object3D.h"
#include <math.h>

class Pavillon : public Object3D
{
    private :
        GLushort verticesArraySize;
        GLushort indicesArraySize;

        GLfloat verticesArray[8*3];
        GLfloat colorsArray[8*3];

        GLuint VertexVBOID;
        GLuint ColorVBOID;
        GLuint IndicesVBOID;

        bool hasInitiatedVBO;

    public:
        Pavillon();
        Pavillon(float radius, float heigth, float heigthFirstLvl, int complexity);
        ~Pavillon();
    protected:
        void initVBO();
        void drawShape(const char *shader_name);
};

#endif // PAVILLON_H
