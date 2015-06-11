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

void Quaternion::setFromAxisAngle(float angle, const Vector3& axis)
{
    Quaternion q(sin(angle/2)*axis, cos(angle/2));
    set(q);
}

void Quaternion::setFromAxisAngle(float angle, float ax, float ay, float az)
{
    Vector3 axis(ax, ay, az);
    setFromAxisAngle(angle, axis);
}

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

void Quaternion::print2() const
{
    char lettres[4] = {'\0', 'i', 'j', 'k'};
    float q[4] = {w, x, y, z};
    ostringstream chaine;

    for (int i = 0; i < 4; ++i)
    {
        if (q[i] != 0)
        {
            if (chaine.str() != "")
            {
                chaine << ((q[i] > 0) ? "+" : "");
            }

            chaine << q[i] << lettres[i];
        }
    }
    
    if (chaine.str() == "")
    {
        chaine << 0;
    }

    cout << chaine.str();
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

Quaternion operator*(float s, const Quaternion& q)
{
    return Quaternion(q*s);
}

/***/

float Quaternion::dot(const Quaternion& q) const
{
    return x*q.getX() + y*q.getY() + z*q.getZ() + w*q.getW();
}

/***/

Quaternion Quaternion::conjugateNew() const
{
    return Quaternion(-x, -y, -z, w);
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

Quaternion Quaternion::normalized() const
{
    return Quaternion(*this/norm());
}

/***/

Quaternion Quaternion::inverseNew() const
{
    return Quaternion(conjugateNew()/normSquared());
}

void Quaternion::invert()
{
    float ns = normSquared();
    x = -x/ns;
    y = -y/ns;
    z = -z/ns;
    w = z/ns;
}

/***/

Quaternion Quaternion::slerp(const Quaternion& q1, const Quaternion& q2, float t)
{
    float theta = angle(q1, q2);
    Quaternion ans((float) (sin(theta*(1-t))/sin(theta)) * q1 + (float) (sin(theta*t)/sin(theta)) * q2);
    ans.normalize();
    return ans;
}

float Quaternion::angle(const Quaternion& q1, const Quaternion& q2)
{
    float a = acos(q1.dot(q2));
    if (a > M_PI)
        a = M_PI*2 - a;
    return a;
    // TODO check this function: return value interval?
}

/***/

Matrix33 Quaternion::getRotationMatrix() const
{
    float matrix[9] = {1-2*y*y-2*z*z, 2*x*y-2*w*z, 2*x*z+2*w*y,
                        2*x*y+2*w*z, 1-2*x*x-2*z*z, 2*y*z-2*w*x,
                        2*x*z-2*w*y, 2*y*z+2*w*x, 1-2*x*x-2*y*y};

    return Matrix33(matrix);

    // FIXME I work with french standards, you might need to transpose the result...
}

void Quaternion::printRotationMatrix() const
{
    Matrix33 matrix = getRotationMatrix();
    matrix.print();
}

/***/

Vector3 Quaternion::image(const Quaternion& q, const Vector3& p)
{
    Quaternion qp(p, 0.0f);
    Quaternion qr(q.normalized());
    Quaternion iqr(qr.inverseNew());
    return (qr*qp*qr.inverseNew()).getV();
}
