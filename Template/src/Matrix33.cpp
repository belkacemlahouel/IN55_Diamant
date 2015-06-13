#include "Matrix33.h"

Matrix33::Matrix33()
{
	for (int i = 0; i < MATRIX_SIZE; ++i)
		matrix[i] = 0;
	transposed = false;
}

Matrix33::Matrix33(float _matrix[])
{
	for (int i = 0; i < MATRIX_SIZE; ++i)
		matrix[i] = _matrix[i];
	transposed = false;
}

Matrix33::Matrix33(float _matrix[], bool transposed) : transposed(transposed)
{
	for (int i = 0; i < MATRIX_SIZE; ++i)
		matrix[i] = _matrix[i];
}

Matrix33::~Matrix33()
{
	// FIXME Maybe I should remove the array?
}

void Matrix33::transpose()
{
	transposed = !transposed;
}

float Matrix33::get(int i, int j) const
{
	if (transposed)
	{
		int tmp = i;
		i = j;
		j = tmp;
	}
	return matrix[MS*i+j];
}

float Matrix33::get(int i) const
{
    return matrix[i];
}

void Matrix33::set(float newMatrix[])
{
	for (int i = 0; i < MATRIX_SIZE; ++i)
		matrix[i] = newMatrix[i];
}

void Matrix33::print() const
{
    for (int i = 0; i < MS; ++i)
    {
        for (int j = 0; j < MS; ++j)
        {
            cout << "\t\t" << get(i, j);
        }
        cout << endl;
    }
}
