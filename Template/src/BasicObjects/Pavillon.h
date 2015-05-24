#ifndef PAVILLON_H
#define PAVILLON_H

#include "Object3D.h"
#include "Types.h"
#include <iostream>
#include <math.h>

using namespace std;

class Pavillon : public Object3D
{
    private :
        GLfloat *pavillonVertices;
        GLushort *pavillonIndices;
        GLfloat *colorsArray;
        /* Array for the last level*/
        GLfloat *pavillonQuadLastLvlVertices;
        GLfloat *pavillonTrianglesLastLvlVertices;
        GLushort *indicesLastLvlTrianglesIndices;
        GLushort *indicesLastLvlQuadIndices;
        GLfloat *colorsLastLvlArray;

        GLushort verticesArraySize;
        GLushort indicesArraySize;
        /* Size of the array of vertices for the last lvl*/
        GLushort verticesQuadLastLvlArraySize;
        GLushort verticesTrianglesLastLvlArraySize;
        GLushort indicesQuadLastLvlArraySize;
        GLushort indicesTrianglesLastLvlArraySize;

        GLuint VertexVBOID;
        GLuint ColorVBOID;
        GLuint IndicesVBOID;
        /* VBO for the second level */
        GLuint VertexQuadVBOID;
        GLuint ColorQuadVBOID;
        GLuint IndicesQuadVBOID;
        GLuint VertexTrianglesVBOID;
        GLuint ColorTrianglesVBOID;
        GLuint IndicesTrianglesVBOID;

        bool hasInitiatedVBO;

    public:
        Pavillon();
        Pavillon(float32 radius, float32 totalHeight, float32 firstLevelHeight, int32 complexity, float32 rondiste, const GLfloat color[3]);
        ~Pavillon();

    protected:
        void initVBO();
        void drawShape(const char *shader_name);
        void createSecondLvl(int32 nbPtLvl1, float32 radius, float32 height, float32 deltaHeight, const GLfloat color[3]);
        void buildQuadrilateral(int32 nbPtLvl1, float32 radius, float32 height,  const GLfloat color[3]);
};

#endif // PAVILLON_H
