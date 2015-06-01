#include "matrix.h"

/**
 * @brief Matrix::Matrix
 * Initialize a identity matrix
 */
Matrix::Matrix()
{
    for(int32 i=0; i<4; ++i)
    {
        for(int32 j=0;j<4;++j)
        {
            if(i!=j)
            {
                matrix[i][j]=0;
            }
            else
            {
                matrix[i][j]=1;
            }
        }
    }
}


/**
 * @brief printMatrix
 * Print all the elements of the current matrix.
 */
void Matrix::printMatrix()
{
    for(int32 i=0; i<4; ++i)
    {
        for(int32 j=0;j<4;++j)
        {
            cout <<  matrix[i][j] << "-";
        }
        cout << endl;
    }
}


/**
 * @brief Matrix::setElement
 * Set an elemet of the matrix at the position given by line and column.
 * @param line
 * @param column
 */
void  Matrix::setElement(int32 line, int32 column, GLfloat value)
{
    matrix[line][column] = value;
}

/**
 * @brief Matrix::productMatVec
 * Calculate the product of the matrix with the vector.
 * @param vector
 * @return the result as a vector.
 */
GLfloat* Matrix::productMatVec(GLfloat* vector)
{
    GLfloat result[4];

    for(int32 i=0; i<4; ++i)
    {
        result[i] = matrix[i][0]*vector[0] + matrix[i][1]*vector[1] + matrix[i][2]*vector[2] + matrix[i][4]*vector[4];
    }
}
