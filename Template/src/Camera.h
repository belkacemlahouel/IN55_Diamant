#ifndef CAMERA_H
#define CAMERA_H

#include <stdio.h>
#include <stdlib.h>
#include "Quaternion.h"
#include "Vector3.h"
#include "Matrix44.h"
#include "Matrix33.h"
#include <math.h>
#include <iostream>

#define DEG2RAD 0.01745329251
#define RAD2DEG 57.2957795131

class Camera
{
private:
    Vector3 m_Position;
    Quaternion m_Orientation;

    Matrix44 m_ViewMatrix;
    Matrix44 m_ProjectionMatrix;

    float aspectRatio, nearPlan, farPlan;
    float fieldOfView; // IN RADIANS

    Vector3 i, j, k;

public:
    Camera();

    void translate(float dx, float dy, float dz);
    void translateX(float dx);
    void translateY(float dy);
    void translateZ(float dz);

    void rotate(float angle, float ax, float ay, float az);
    void rotate(float angle, const Vector3& axis);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);

    void setAspectRatio(float ar);
    void setPlanes(float np, float  fp);
    void setFieldOfView(float angle);

    Matrix44 getViewMatrix() const;
    Matrix44 getProjectionMatrix() const;

protected:
    void buildViewMatrix();
    void buildProjectionMatrix();
};

#endif // CAMERA_H
