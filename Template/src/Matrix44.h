#ifndef MATRIX44_H
#define MATRIX44_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "Vector3.h"
#include <sstream>

#define MATRIX44_SIZE 16
#define MS44 4

using namespace std;

class Matrix44
{
private:
    float matrix[MATRIX44_SIZE];
    bool transposed;

public:
	Matrix44();
	Matrix44(float matrix[]);
	Matrix44(float matrix[], bool transposed);
	~Matrix44();
	void transpose();
	float get(int i, int j) const;
	void set(float newMatrix[]);
	void print() const;
};

#endif // MATRIX44_H
