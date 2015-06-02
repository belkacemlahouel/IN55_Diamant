#ifndef CROWN_H
#define CROWN_H

#include "Object3D.h"
#include "Types.h"
#include "Tools/matrix.h"
#include <iostream>
#include <math.h>

using namespace std;

class Crown : public Object3D
{
    private :
        GLfloat *verticesPrincipalFacesUpArray;
        GLfloat *verticesLittleFacesUpArray;
        GLfloat *verticesTrianglesDownArray;
        GLushort *indicesPrincipalArray;
        GLushort *indicesLittleFacesUpArray;
        GLushort *indicesLittleFacesDownArray;
        GLfloat *colorsPrincipalArray;
        GLfloat *colorsTrianglesDownArray;

        GLushort verticesPrincipalArraySize;
        GLushort verticesTrianglesDownArraySize;
        GLushort indicesPrincipalArraySize;
        GLushort indicesLittleFacesDownArraySize;
        GLushort colorsPrincipalArraySize;

        GLuint VertexPrincipalFacesVBOID;
        GLuint ColorPrincipalFacesVBOID;
        GLuint IndicesPrincipalFacesVBOID;

        GLuint VertexUpperTrianglesVBOID;
        GLuint ColorUpperTrianglesVBOID;
        GLuint IndicesUpperTrianglesVBOID;

        bool  hasInitiatedVBO;
    public:
        Crown();
        Crown(float32 radius, float32 table, float32 crownHeight, float32 rondisteHeight, float32 pavillonHeight, float32 lvlCrownHeight, int32 complexity, const GLfloat color[3]);
        ~Crown();
        void createDownTriangles(float32 radius, float32 table, float32 crownHeight, float32 rondisteHeight, float32 pavillonHeight, float32 lvlCrownHeight, int32 complexity, const GLfloat color[3]);

    protected :
        void initVBO();
        void drawShape(const char *shader_name);
};

#endif // CROWN_H
