#include "Camera.h"

Camera::Camera() : fieldOfView(70.0f*DEG2RAD), farPlan(20.0f), nearPlan(5.0f), aspectRatio(0.7f)
{
    i = Vector3(1.0f, 0.0f, 0.0f);
    j = Vector3(0.0f, 1.0f, 0.0f);
    k = Vector3(0.0f, 0.0f, 1.0f);

    m_Position = Vector3(0.0f, -6.0f, -20.0f);
    m_Orientation = Quaternion(0.0f, 1.0f, 0.0f, 0.0f);

    buildProjectionMatrix();
    buildViewMatrix();
}

void Camera::reset()
{
//    fieldOfView = 70.0f*DEG2RAD;
//    farPlan = 20.0f;
//    nearPlan = 5.0f;
//    aspectRatio = 0.7f;
    m_Position = Vector3(0.0f, -6.0f, -20.0f);
    m_Orientation = Quaternion(0.0f, 1.0f, 0.0f, 0.0f);

    buildProjectionMatrix();
    buildViewMatrix();
}
/***/

void Camera::translate(float dx, float dy, float dz)
{
    translateX(dx);
    translateY(dy);
    translateZ(dz);
}

void Camera::translateX(float dx)
{
    m_Position += Quaternion::image(m_Orientation, i) * dx;
}

void Camera::translateY(float dy)
{
    m_Position += Quaternion::image(m_Orientation, j) * dy;
}

void Camera::translateZ(float dz)
{
    m_Position += Quaternion::image(m_Orientation, k) * dz;
}

/***/

// TODO Check that
// Should I not rotate my axis then turn around it?

void Camera::rotate(float angle, float ax, float ay, float az)
{
    Quaternion rotation;
    rotation.setFromAxisAngle(angle, ax, ay, az);
    rotation.normalize();

    // m_Orientation *= rotation.inverseNew();
    m_Orientation.normalize();
    m_Orientation = rotation * m_Orientation;
    m_Orientation.normalize();

    // m_Position = Quaternion::image(rotation, m_Position);
}

void Camera::rotateX(float angle)
{
    rotate(angle, i.getX(), i.getY(), i.getZ());
}

void Camera::rotateY(float angle)
{
    rotate(angle, j.getX(), j.getY(), j.getZ());

}

void Camera::rotateZ(float angle)
{
    rotate(angle, k.getX(), k.getY(), k.getZ());
}

/***/

void Camera::setAspectRatio(float ar)
{
    aspectRatio = ar;
}

void Camera::setPlanes(float np, float  fp)
{
    nearPlan = np;
    farPlan = fp;
}

void Camera::setFieldOfView(float angle)
{
    fieldOfView = angle;
}

/***/

Matrix44 Camera::getViewMatrix() const
{
    return m_ViewMatrix;
}

Matrix44 Camera::getProjectionMatrix() const
{
    return m_ProjectionMatrix;
}

GLMatrix Camera::getViewGLMatrix()
{
    Matrix44 view;
    view = getViewMatrix();
    view.transpose();

    GLMatrix glView;
    for (int i = 0; i < MS44; ++i)
        for (int j = 0; j < MS44; ++j)
            glView.data[i+MS44*j] = view.get(i, j);

    view.transpose();
    return glView;

    /***/

//    m_Orientation.normalize();

//    Matrix33 R = m_Orientation.getRotationMatrix();

//    GLfloat RPx = R.get(0) * m_Position.getX() + R.get(1) * m_Position.getY() + R.get(2) * m_Position.getZ();
//    GLfloat RPy = R.get(3) * m_Position.getX() + R.get(4) * m_Position.getY() + R.get(5) * m_Position.getZ();
//    GLfloat RPz = R.get(6) * m_Position.getX() + R.get(7) * m_Position.getY() + R.get(8) * m_Position.getZ();

//    GLMatrix viewMatrix;

//    float tmp[16] =    {R.get(0),R.get(1),R.get(2),-RPx,
//                        R.get(3),R.get(4),R.get(5),-RPy,
//                        R.get(6),R.get(7),R.get(8),-RPz,
//                        0.0f,    0.0f,    0.0f,    1.0f};

//    viewMatrix.set(tmp);

//    return viewMatrix;
}

GLMatrix Camera::getProjectionGLMatrix() const
{
    Matrix44 proj;
    proj = getProjectionMatrix();
    proj.transpose();

    GLMatrix glProj;
    for (int i = 0; i < MS44; ++i)
        for (int j = 0; j < MS44; ++j)
            glProj.data[i+MS44*j] = proj.get(i, j);

    proj.transpose();
    return glProj;
}

/***/

void Camera::buildViewMatrix()
{
    Vector3 ni(Quaternion::image(m_Orientation, i));
    Vector3 nj(Quaternion::image(m_Orientation, j));
    Vector3 nk(Quaternion::image(m_Orientation, k));

    float view[MATRIX44_SIZE] = {ni.getX(), nj.getX(), nk.getX(), m_Position.getX(),
                                 ni.getY(), nj.getY(), nk.getY(), m_Position.getY(),
                                 ni.getZ(), nj.getZ(), nk.getZ(), m_Position.getZ(),
                                 0.0f,      0.0f,      0.0f,      1.0f};
    //    i = ni;
    //    j = nj;
    //    k = nk;

    m_ViewMatrix = Matrix44(view);

    // m_ViewMatrix.print();
}

void Camera::buildProjectionMatrix()
{
    float n = nearPlan;
    float f = farPlan;
    float e = 1/(tan(fieldOfView/2.0f));
    float r = n/e;
    float l = -r;
    float t = n*aspectRatio/e;
    float b = -t;

    float proj[MATRIX44_SIZE] = {2*n/(r-l), 0.0f,       (r+l)/(r-l),    0.0f,
                                 0.0f,      2*n/(t-b),  (t+b)/(t-b),    0.0f,
                                 0.0f,      0.0f,       (f+n)/(n-f),    2*n*f/(n-f),
                                 0.0f,      0.0f,       -1.0f,          0.0f};

    m_ProjectionMatrix = Matrix44(proj);

    // m_ViewMatrix.print();
}
