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

    GLint m_id = glGetUniformLocation(m_Framework->getCurrentShaderId(), "M");
    GLint v_id = glGetUniformLocation(m_Framework->getCurrentShaderId(), "V");
    GLint p_id = glGetUniformLocation(m_Framework->getCurrentShaderId(), "P");
    GLint mv_id = glGetUniformLocation(m_Framework->getCurrentShaderId(), "MV");
    GLint mvp_id = glGetUniformLocation(m_Framework->getCurrentShaderId(), "MVP");

    m_Framework->transmitM(m_id);
    m_Framework->transmitV(v_id);
    m_Framework->transmitP(p_id);
    m_Framework->transmitMV(mv_id);
    m_Framework->transmitMVP(mvp_id);

    drawShape();
}
void Object3D::draw(const char* shader_name)
{
    std::cout << m_Framework->getCurrentShaderId() << std::endl;
    if (m_Framework->useShader(shader_name))
    {
        m_Framework->computeAncillaryMatrices();

        GLint nm_id = glGetUniformLocation(m_Framework->getCurrentShaderId(), "NM");
        GLint mv_id = glGetUniformLocation(m_Framework->getCurrentShaderId(), "MV");
        GLint mvp_id = glGetUniformLocation(m_Framework->getCurrentShaderId(), "MVP");

        m_Framework->transmitNM(nm_id);
        m_Framework->transmitMV(mv_id);
        m_Framework->transmitMVP(mvp_id);

        drawShape(shader_name);
        std::cout << m_Framework->getCurrentShaderId() << std::endl;
    }
}

bool Object3D::setAlpha(GLfloat alpha)
{
    GLint alphaLocation = glGetUniformLocation(m_Framework->getCurrentShaderId(), "alpha");

    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if(alphaLocation != -1)
    {
        glUniform1f(alphaLocation, alpha);
        std::cout << "Uniform 'alpha' changed to : " << alpha << std::endl;
        return true;
    }
    return false;
}

GLfloat* Object3D::ComputeSurfaceNormal (GLfloat p1[3], GLfloat p2[3], GLfloat p3[3])
{
    GLfloat normal[3];

    GLfloat U[3];
    GLfloat V[3];
    for(int i=0; i<3; i++)
    {
        U[i] = p2[i] - p1[i];
        V[i] = p3[i] - p1[i];
    }

    normal[0] = (U[2] * V[3]) - (U[3] * V[2]);
    normal[1] = (U[3] * V[1]) - (U[1] * V[3]);
    normal[2] = (U[1] * V[2]) - (U[2] * V[1]);

    return normal;
}
