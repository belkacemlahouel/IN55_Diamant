#include "Vector3.h"

Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f)
{

}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{

}

Vector3::~Vector3()
{

}

Vector3::Vector3(const Vector3& v) : x(v.getX()), y(v.getY()), z(v.getZ())
{

}

/***/

float Vector3::getX() const
{
    return x;
}

float Vector3::getY() const
{
    return y;
}

float Vector3::getZ() const
{
    return z;
}

void Vector3::set(float newx, float newy, float newz)
{
    this->x = newx;
    this->y = newy;
    this->z = newz;
}

void Vector3::setX(float newx)
{
    this->x = newx;
}

void Vector3::setY(float newy)
{
    this->y = newy;
}

void Vector3::setZ(float newz)
{
    this->z = newz;
}

/***/

void Vector3::print() const
{
    printf("(%0.1f, %0.1f, %0.1f)", x, y, z);
}

/***/

Vector3 Vector3::operator+(const Vector3& v) const
{
    return Vector3(x+v.x, y+v.y, z+v.z);
}

Vector3 Vector3::operator-(const Vector3& v) const
{
    return Vector3(x-v.x, y-v.y, z-v.z);
}

Vector3 Vector3::operator*(float s) const
{
    return Vector3(x*s, y*s, z*s);
}

Vector3 operator*(float s, const Vector3& v)
{
    return Vector3(v.getX()*s, v.getY()*s, v.getZ()*s);
}

Vector3 Vector3::operator/(float s) const
{
    return (*this) * (1/s);
}

void Vector3::operator+=(const Vector3& v)
{
    *this = *this + v;
}

void Vector3::operator-=(const Vector3& v)
{
    *this = *this - v;
}

void Vector3::operator*=(float s)
{
    *this = (*this) * s;
}

void Vector3::operator/=(float s)
{
    *this = (*this) / s;
}

/***/

Vector3 Vector3::cross(const Vector3& v) const
{
    float _x, _y, _z;
    _x = y*v.getZ() - z*v.getY();
    _y = z*v.getX() - x*v.getZ();
    _z = x*v.getY() - y*v.getX();
    return Vector3(_x, _y, _z);
}

float Vector3::dot(const Vector3& v) const
{
    return v.getX()*x + v.getY()*y + v.getZ()*z;
}

/***/

Vector3 Vector3::cross(const Vector3& v1, const Vector3& v2)
{
    return v1.cross(v2);
}

float Vector3::dot(const Vector3& v1, const Vector3& v2)
{
    return v1.dot(v2);
}

Vector3 Vector3::linearInterpolation(const Vector3& v1, const Vector3& v2, float t)
{
    return Vector3((1-t)*v1 + t*v2);
}

