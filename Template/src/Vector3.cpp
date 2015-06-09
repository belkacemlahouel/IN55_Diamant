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

void Vector3::print()
{
    printf("(%0.1f, %0.1f, %0.1f)", x, y, z);
}

/***/

void Vector3::plus(const Vector3& v)
{
    x += v.getX();
    y += v.getY();
    z += v.getZ();
}

void Vector3::minus(const Vector3& v)
{
    x -= v.getX();
    y -= v.getY();
    z -= v.getZ();
}

void Vector3::scale(float s)
{
    x *= s;
    y *= s;
    z *= s;
}

Vector3 Vector3::cross(const Vector3& v)
{
    float x, y, z;
    x = y*v.getZ() - z*v.getY();
    y = x*v.getZ() - z*v.getX();
    z = x*v.getY() - y*v.getX();
    return Vector3(x, y, z);
}

float Vector3::dot(const Vector3& v)
{
    return v.getX()*x + v.getY()*y + v.getZ()*z;
}

/***/

Vector3 Vector3::plus(const Vector3& v1, const Vector3& v2)
{
    Vector3 ans(v1);
    ans.plus(v2);
    return ans;
}

Vector3 Vector3::minus(const Vector3& v1, const Vector3& v2)
{
    Vector3 ans(v1);
    ans.minus(v2);
    return ans;
}

Vector3 Vector3::scale(const Vector3& v1, float s)
{
    Vector3 ans(v1);
    ans.scale(s);
    return ans;
}

Vector3 Vector3::cross(const Vector3& v1, const Vector3& v2)
{
    Vector3 ans(v1);
    return ans.cross(v2);
}

float Vector3::dot(const Vector3& v1, const Vector3& v2)
{
    Vector3 ans(v1);
    return ans.dot(v2);
}
