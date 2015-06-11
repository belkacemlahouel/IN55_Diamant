#ifndef QUATERNION_H
#define QUATERNION_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "Vector3.h"
#include <sstream>
#include "Matrix33.h"

using namespace std;

class Quaternion
{
private:
    float x, y, z, w;

public:
	Quaternion(float x, float y, float z, float w);
	Quaternion(const Quaternion& q);
	Quaternion(const Vector3& v, float w);
	Quaternion();
	~Quaternion();

	float getX() const;
    float getY() const;
    float getZ() const;
    float getW() const;
    Vector3 getV() const;

	void set(const Quaternion& q);
    void setFromAxisAngle(float angle, float ax, float ay, float az);
    void setFromAxisAngle(float angle, const Vector3& axis);
    void set(float a, float b, float c, float d);
    void setX(float a);
    void setY(float b);
    void setZ(float c);
    void setW(float d);

    void print() const;
    void print2() const;

    Quaternion operator+(const Quaternion& q) const;
    Quaternion operator-(const Quaternion& q) const;
    Quaternion operator*(const Quaternion& q) const;
    Quaternion operator*(float s) const;
    Quaternion operator/(float s) const;
    void operator=(const Quaternion& q);
    void operator-=(const Quaternion& q);
    void operator+=(const Quaternion& q);
    void operator*=(const Quaternion& q);
    void operator*=(float s);
    void operator/=(float s);

    float dot(const Quaternion& q) const;

    Quaternion conjugateNew() const;
    void conjugue();

    float norm() const;
    float normSquared() const;

    Quaternion normalized() const;
    void normalize();

    Quaternion inverseNew() const;
    void invert();

    static Quaternion slerp(const Quaternion& q1, const Quaternion& q2, float t);
    static float angle(const Quaternion& q1, const Quaternion& q2);
    
    Matrix33 getRotationMatrix() const;
    void printRotationMatrix() const;

    static Vector3 image(const Quaternion& q, const Vector3& p);
};

Quaternion operator*(float s, const Quaternion& q);

#endif // QUATERNION_H
