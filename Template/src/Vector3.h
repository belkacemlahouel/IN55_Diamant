#ifndef VECTOR3_H
#define VECTOR3_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

class Vector3
{
private:
float x, y, z;

public:
Vector3(float x, float y, float z);
Vector3(const Vector3& v);
Vector3();
~Vector3();

float getX() const;
float getY() const;
float getZ() const;

void set(float newx, float newy, float newz);
void setX(float newx);
void setY(float newy);
void setZ(float newz);

void print();

void plus(const Vector3& v);
void minus(const Vector3& v);
void scale(float f);
Vector3 cross(const Vector3& v);
float dot(const Vector3& v);

static Vector3 plus(const Vector3& v1, const Vector3& v2);
static Vector3 minus(const Vector3& v1, const Vector3& v2);
static Vector3 scale(const Vector3& v, float s);
static Vector3 cross(const Vector3& v1, const Vector3& v2);
static float dot(const Vector3& v1, const Vector3& v2);
};

#endif // VECTOR3_H
