#include "Object3D.h"
#include <iostream>

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
    m_Framework->computeAncillaryMatrices();
    GLint var_id = glGetUniformLocation(m_Framework->getCurrentShaderId(), "MVP");
    m_Framework->transmitMVP(var_id);

    drawShape();
}
void Object3D::draw(const char* shader_name)
{
    std::cout << m_Framework->getCurrentShaderId() << std::endl;
    if (m_Framework->useShader(shader_name))
    {
        m_Framework->computeAncillaryMatrices();
        GLint var_id = glGetUniformLocation(m_Framework->getCurrentShaderId(), "MVP");
        m_Framework->transmitMVP(var_id);

        drawShape(shader_name);
        std::cout << m_Framework->getCurrentShaderId() << std::endl;
    }
}
