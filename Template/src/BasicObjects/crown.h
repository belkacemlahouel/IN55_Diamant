#ifndef CROWN_H
#define CROWN_H

#include "Object3D.h"
#include "Types.h"
#include <iostream>
#include <math.h>

class Crown : public Object3D
{
    private :
        GLfloat *verticesPrincipalFacesUpArray;
        GLfloat *verticesLittleFacesUpArray;
        GLushort *indicesPrincipalArray;
        GLushort *indicesLittleFacesArray;
        GLfloat *colorsPrincipalArray;
        GLfloat *colorsLittleFacesArray;

        GLushort verticesPrincipalArraySize;
        GLushort verticesLittleFacesArraySize;
        GLushort indicesPrincipalArraySize;
        GLushort indicesLittleFacesArraySize;
        GLushort colorsPrincipalArraySize;
        GLushort colorsLittleFacesArraySize;

        GLuint VertexVBOID;
        GLuint ColorVBOID;
        GLuint IndicesVBOID;

        bool  hasInitiatedVBO;
    public:
        Crown();
        Crown(float32 radius, float32 table, float32 crownHeight, float32 rondisteHeight, float32 pavillonHeight, float32 lvlCrownHeight, int32 complexity, const GLfloat color[3]);
        ~Crown();

    protected :
        void initVBO();
        void drawShape(const char *shader_name);
};

#endif // CROWN_H
