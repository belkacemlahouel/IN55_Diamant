#ifndef QUATERNION_H
#define QUATERNION_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "Vector3.h"

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
    void set(float a, float b, float c, float d);
    void setX(float a);
    void setY(float b);
    void setZ(float c);
    void setW(float d);

    void print() const;

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
    void normalize();

    Quaternion inverseNew() const;
    void invert();

    static Quaternion slerp(const Quaternion& q1, const Quaternion& q2, float t);
    static float angle(const Quaternion& q1, const Quaternion& q2);
    
    // void setFromAxisAngle(float angle, float ax, float ay, float az);
    // void setRotationMatrix(float* mat);
};

Quaternion operator*(float s, const Quaternion& q);

#endif // QUATERNION_H

/*
void rotate(float _angle, glm::vec3& _axis);
static Quaternion computeRotationQuaternion(float _angle, glm::vec3& _axis);
static Quaternion computeRotationQuaternion(float _rx, float _ry, float _rz);
static void computeRotationQuaternion(float _angle, glm::vec3& _axis, Quaternion& _out);
static void computeRotationQuaternion(float _rx, float _ry, float _rz, Quaternion& _out);

explicit operator glm::mat4() const
{
	return glm::mat4(
		1 - 2*c*c - 2*d*d, 2*b*c - 2*d*a, 2*b*d + 2*c*a, 0,
		2*b*c + 2*d*a, 1 - 2*b*b - 2*d*d, 2*c*d - 2*b*a, 0,
		2*b*d - 2*c*a, 2*c*d + 2*b*a, 1 - 2*b*b - 2*c*c, 0,
		0, 0, 0, 1);
};

static Quaternion quat_rotate(float _angle, glm::vec3& _axis);
*/
