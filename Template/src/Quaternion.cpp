#include "Quaternion.h"

Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{

}

Quaternion::Quaternion(const Quaternion& q) : x(q.getX()), y(q.getY()), z(q.getZ()), w(q.getW())
{

}

Quaternion::Quaternion(const Vector3& v, float w) : x(v.getX()), y(v.getY()), z(v.getZ()), w(w)
{

}

Quaternion::Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{

}

Quaternion::~Quaternion()
{

}

/***/

float Quaternion::getX() const
{
    return x;
}

float Quaternion::getY() const
{
    return y;
}

float Quaternion::getZ() const
{
    return z;
}

float Quaternion::getW() const
{
    return w;
}

Vector3 Quaternion::getV() const
{
    return Vector3(x, y, z);
}

/***/

void Quaternion::set(const Quaternion& q)
{
    set(q.x, q.y, q.z, q.w);
}

void Quaternion::set(float a, float b, float c, float d)
{
    x = a;
    y = b;
    z = c;
    w = d;
}

void Quaternion::setX(float a)
{
    x = a;
}

void Quaternion::setY(float b)
{
    y = b;
}

void Quaternion::setZ(float c)
{
    z = c;
}

void Quaternion::setW(float d)
{
    w = d;
}

/***/

void Quaternion::print() const
{
    printf("(%0.1f, %0.1f, %0.1f, %0.1f)", x, y, z, w);
}

/***/

Quaternion Quaternion::operator+(const Quaternion& q) const
{
    return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w);
}

Quaternion Quaternion::operator-(const Quaternion& q) const
{
    return Quaternion(x - q.x, y - q.y, z - q.z, w - q.w);
}

Quaternion Quaternion::operator*(const Quaternion& q) const
{
    return Quaternion(w*q.getV() + q.getW()*getV() + getV().cross(q.getV()),
                        w*q.w - getV().dot(q.getV()));
}

void Quaternion::operator=(const Quaternion& q)
{
    set(q.x, q.y, q.z, q.w);
}

Quaternion Quaternion::operator*(float s) const
{
    return Quaternion(x*s, y*s, z*s, w*s);
}

Quaternion Quaternion::operator/(float s) const
{
    return Quaternion(x/s, y/s, z/s, w/s);
}

void Quaternion::operator-=(const Quaternion& q)
{
    this->set((*this)-q);
}

void Quaternion::operator+=(const Quaternion& q)
{
    this->set((*this)+q);
}

void Quaternion::operator*=(const Quaternion& q)
{
    this->set((*this)*q);
}

void Quaternion::operator*=(float s)
{
    this->set((*this)*s);
}

void Quaternion::operator/=(float s)
{
    this->set((*this)/s);
}


/***/

float Quaternion::dot(const Quaternion& q)
{
    return x*q.getX() + y*q.getY() + z*q.getZ() + w*q.getW();
}

/***/

Quaternion Quaternion::conjugate(const Quaternion& q) const
{
    return Quaternion(-q.x, -q.y, -q.z, q.w);
}

void Quaternion::conjugue()
{
    x = -x;
    y = -y;
    z = -z;
}

/***/

float Quaternion::norm() const
{
    return (float) sqrt(x*x + y*y + z*z + w*w);   
}

float Quaternion::normSquared() const
{
    return (float) x*x + y*y + z*z + w*w;
}

void Quaternion::normalize()
{
    *this/=norm();
}



/*
void Quaternion::normalize() {
    float size = norm();
    x /= size;
    y /= size;
    z /= size;
    w /= size;
}
*/

/*


void Quaternion::invert()
{
    float norm = normSquared(*this);
    a = a / norm;
    b = b / norm;
    c = c / norm;
    d = d / norm;
}

void Quaternion::normalize()
{
    float norm = normSquared(*this);
    set(a / norm, b / norm, c / norm, d / norm);
}

void Quaternion::rotate(float _angle, glm::vec3& _axis)
{
    Quaternion q = computeRotationQuaternion(_angle, _axis);
    set(a*q.a - b*q.b - c*q.c - d*q.d,
        b*q.a + a*q.b + d*q.c - c*q.d,
        c*q.a + a*q.c + b*q.d - d*q.b,
        d*q.a + a*q.d + c*q.b - b*q.c);

    normalize();
}

Quaternion Quaternion::operator/(const Quaternion& q) const
{
    return (*this)*invert(q); // equivalent to Q1*invert(Q2)
}

float Quaternion::normSquared(const Quaternion& q)
{
    return q.a*q.a + q.b*q.b + q.c*q.c + q.d*q.d;
}

Quaternion Quaternion::invert(const Quaternion& q)
{
    float normSquared = Quaternion::normSquared(q);
    return Quaternion(q.a / normSquared, -q.b / normSquared, -q.c / normSquared, -q.d / normSquared);
}

std::string Quaternion::toString(const Quaternion& q)
{
    std::stringstream str;
    str << "[ " << q.a << " " << q.b << " " << q.c << " " << q.d << " ]";
    return str.str();
}

Quaternion Quaternion::quat_rotate(float _angle, glm::vec3& _axis)
{
    glm::vec3 axisNorm = glm::normalize(_axis);
    float sinAngle = sinf(_angle / 2.0f);
    float cosAngle = cosf(_angle / 2.0f);

    return Quaternion(cosAngle, sinAngle*axisNorm.x, sinAngle*axisNorm.y, sinAngle*axisNorm.z);

}

Quaternion Quaternion::computeRotationQuaternion(float _angle, glm::vec3& _axis)
{
    glm::vec3 axisNorm = glm::normalize(_axis);
    float halfAngle = _angle / 2.0f;
    float sinAngle = sinf(halfAngle);
    return Quaternion(cosf(halfAngle), sinAngle*_axis.x, sinAngle*_axis.y, sinAngle*_axis.z);
}

Quaternion Quaternion::computeRotationQuaternion(float _rx, float _ry, float _rz)
{
    float halfrx = _rx / 2.0f;
    float halfry = _ry / 2.0f;
    float halfrz = _rz / 2.0f;

    float cosrx = cosf(halfrx);
    float sinrx = sinf(halfrx);
    float cosry = cosf(halfry);
    float sinry = sinf(halfry);
    float cosrz = cosf(halfrz);
    float sinrz = sinf(halfrz);

    return Quaternion(cosrx*cosry*cosrz - sinrx*sinry*sinrz,
        cosry*cosrz*sinrx + cosrx*sinry*sinrz,
        cosrx*cosrz*sinry - cosry*sinrx*sinrz,
        cosrx*cosry*sinrz + cosrz*sinrx*sinry);
}

void Quaternion::computeRotationQuaternion(float _angle, glm::vec3& _axis, Quaternion& _out)
{
    glm::vec3 axisNorm = glm::normalize(_axis);
    float halfAngle = _angle / 2.0f;
    float sinAngle = sin(halfAngle);
    _out.set(cosf(halfAngle), sinAngle*_axis.x, sinAngle*_axis.y, sinAngle*_axis.z);
}

void Quaternion::computeRotationQuaternion(float _rx, float _ry, float _rz, Quaternion& _out)
{
    float halfrx = _rx / 2.0f;
    float halfry = _ry / 2.0f;
    float halfrz = _rz / 2.0f;

    float cosrx = cosf(halfrx);
    float sinrx = sinf(halfrx);
    float cosry = cosf(halfry);
    float sinry = sinf(halfry);
    float cosrz = cosf(halfrz);
    float sinrz = sinf(halfrz);

    _out.set(cosrx*cosry*cosrz - sinrx*sinry*sinrz,
        cosry*cosrz*sinrx + cosrx*sinry*sinrz,
        cosrx*cosrz*sinry - cosry*sinrx*sinrz,
        cosrx*cosry*sinrz + cosrz*sinrx*sinry);
}
*/
