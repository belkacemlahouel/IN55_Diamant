#include "Matrix44.h"

Matrix44::Matrix44()
{
	for (int i = 0; i < MATRIX44_SIZE; ++i)
		matrix[i] = 0;
	transposed = false;
}

Matrix44::Matrix44(float _matrix[])
{
	for (int i = 0; i < MATRIX44_SIZE; ++i)
		matrix[i] = _matrix[i];
	transposed = false;
}

Matrix44::Matrix44(float _matrix[], bool transposed) : transposed(transposed)
{
	for (int i = 0; i < MATRIX44_SIZE; ++i)
		matrix[i] = _matrix[i];
}

Matrix44::~Matrix44()
{
	// FIXME Maybe I should remove the array?
}

void Matrix44::transpose()
{
	transposed = !transposed;
}

float Matrix44::get(int i, int j) const
{
	if (transposed)
	{
		int tmp = i;
		i = j;
		j = tmp;
	}
	return matrix[MS44*i+j];
}

void Matrix44::set(float newMatrix[])
{
	for (int i = 0; i < MATRIX44_SIZE; ++i)
		matrix[i] = newMatrix[i];
}

void Matrix44::print() const
{
    for (int i = 0; i < MS44; ++i)
    {
        for (int j = 0; j < MS44; ++j)
        {
            cout << "\t\t" << get(i, j);
        }
        cout << endl;
    }
}
