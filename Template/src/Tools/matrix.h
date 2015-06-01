#ifndef MATRIX_H
#define MATRIX_H

#include "Types.h"
#include "Object3D.h"
#include <iostream>

using namespace std;


class Matrix
{
    private:
        GLfloat matrix[4][4]; /* The matrix is defined as following : 4 lines X 4 columns */
    public:
        Matrix(); /* Initialize a identity matrix */
        void printMatrix();
        void setElement(int32 line, int32 column, GLfloat value);
        GLfloat* productMatVec(GLfloat* vector);
};

#endif // MATRIX_H
