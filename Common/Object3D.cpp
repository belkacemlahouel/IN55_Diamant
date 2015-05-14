﻿#include "Object3D.h"

AbstractFramework* Object3D::m_Framework = NULL;

Object3D::~Object3D()
{
    /* TODO */
}

void Object3D::setFramework( AbstractFramework* fw )
{
	m_Framework = fw;
}

void Object3D::draw()
{
    if (m_Framework->useShader("defaultDiffuseShader"))
    {
        m_Framework->computeAncillaryMatrices();
        GLint var_id = glGetUniformLocation(m_Framework->getCurrentShaderId(), "MVP");
        m_Framework->transmitMVP(var_id);

        drawShape("defaultDiffuseShader");
    }
}
void Object3D::draw(const char* shader_name)
{
    if (m_Framework->useShader(shader_name))
    {
        m_Framework->computeAncillaryMatrices();
        GLint var_id = glGetUniformLocation(m_Framework->getCurrentShaderId(), "MVP");
        m_Framework->transmitMVP(var_id);

        drawShape(shader_name);
    }
}
