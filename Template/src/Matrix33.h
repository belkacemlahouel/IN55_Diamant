#ifndef MATRIX33_H
#define MATRIX33_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "Vector3.h"
#include <sstream>

#define MATRIX_SIZE 9
#define MS 3

using namespace std;

class Matrix33
{
private:
    float matrix[MATRIX_SIZE];
    bool transposed;

public:
	Matrix33();
	Matrix33(float matrix[]);
	Matrix33(float matrix[], bool transposed);
	~Matrix33();
	void transpose();
	float get(int i, int j) const;
    float get(int i) const;
	void set(float newMatrix[]);
	void print() const;
};

#endif // MATRIX33_H
