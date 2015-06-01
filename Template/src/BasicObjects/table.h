#ifndef TABLE_H
#define TABLE_H

#include "Object3D.h"
#include "Types.h"
#include <iostream>
#include <math.h>

using namespace std;

class Table
{
    private:
        GLfloat *vertices;
        GLushort *indices;
        GLushort *colors;

        bool  hasInitiatedVBO;

    public:
        Table();
        Table(float32 radiusTable, float32 heightCrown, float32 heightPavillon);
        ~Table();

    protected :
        void initVBO();
        void drawShape(const char *shader_name);
};

#endif // TABLE_H
