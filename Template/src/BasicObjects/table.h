#ifndef TABLE_H
#define TABLE_H

#include "Object3D.h"
#include "Types.h"
#include <iostream>
#include <math.h>

using namespace std;

class Table : public Object3D
{
    private:
        GLfloat *verticesArray;
        GLushort *indicesArray;
        GLfloat *colorsArray;

        GLushort verticesArraySize;
        GLushort indicesArraySize;
        GLushort colorsArraySize;

        GLuint VerticesVBOID;
        GLuint ColorsVBOID;
        GLuint IndicesVBOID;

        bool  hasInitiatedVBO;

    public:
        Table();
        Table(float32 radiusTable, float32 heightCrown, float32 heightPavillon, int32 complexity, const GLfloat color[3]);
        ~Table();

    protected :
        void initVBO();
        void drawShape(const char *shader_name);
        void computeNormals();
};

#endif // TABLE_H
