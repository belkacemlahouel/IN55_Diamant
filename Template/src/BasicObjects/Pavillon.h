#ifndef PAVILLON_H
#define PAVILLON_H

#include "Object3D.h"
#include "Types.h"
#include <iostream>
#include <math.h>

class Pavillon : public Object3D
{
    private :
        GLfloat *pavillonVertices;
        GLushort *pavillonIndices;
        GLfloat *colorsArray;
        /* Array for the last level*/
        GLfloat *pavillonLastLvlVertices;
        GLushort *pavillonLastLvlIndices;
        GLfloat *colorsLastLvlArray;

        GLushort verticesArraySize;
        GLushort indicesArraySize;

        GLuint VertexVBOID;
        GLuint ColorVBOID;
        GLuint IndicesVBOID;

        bool hasInitiatedVBO;

    public:
        Pavillon();
        Pavillon(float32 radius, float32 height, float32 heightFirstLvl, int32 complexity, const GLfloat color[3]);
        ~Pavillon();

    protected:
        void initVBO();
        void drawShape(const char *shader_name);
        void createSecondLvl(int32 nbPtLvl1, float32 radius, float32 height,  const GLfloat color[3]);
};

#endif // PAVILLON_H
