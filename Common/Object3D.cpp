#include "Object3D.h"
#include <iostream>

using namespace std;

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

    GLint v_id = glGetUniformLocation(m_Framework->getCurrentShaderId(), "V");
    GLint nm_id = glGetUniformLocation(m_Framework->getCurrentShaderId(), "NM");
    GLint mv_id = glGetUniformLocation(m_Framework->getCurrentShaderId(), "MV");
    GLint mvp_id = glGetUniformLocation(m_Framework->getCurrentShaderId(), "MVP");

    m_Framework->transmitNM(v_id);
    m_Framework->transmitNM(nm_id);
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

        GLint v_id = glGetUniformLocation(m_Framework->getCurrentShaderId(), "V");
        GLint nm_id = glGetUniformLocation(m_Framework->getCurrentShaderId(), "NM");
        GLint mv_id = glGetUniformLocation(m_Framework->getCurrentShaderId(), "MV");
        GLint mvp_id = glGetUniformLocation(m_Framework->getCurrentShaderId(), "MVP");

        m_Framework->transmitNM(v_id);
        m_Framework->transmitNM(nm_id);
        m_Framework->transmitMV(mv_id);
        m_Framework->transmitMVP(mvp_id);

        drawShape(shader_name);
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

    cout.flush();
    return normal;
}
void Object3D::computeNormals(GLfloat *normals, GLfloat *vertices, GLushort nbVertices, GLushort *indices, GLushort nbIndices, bool isTriangleFan)
{
    GLfloat *tmpNormal;
    GLfloat p1[3], p2[3], p3[3];
    GLushort v1, v2, v3;

    if(isTriangleFan)
    {
        v1 = indices[0]*3;
        p1[0] = vertices[v1];
        p1[1] = vertices[v1+1];
        p1[2] = vertices[v1+2];

        for(GLushort i=1; i<nbIndices; i=i+1)
        {
            v2 = indices[i]*3;
            p2[0] = vertices[v2];
            p2[1] = vertices[v2+1];
            p2[2] = vertices[v2+2];

            v3 = indices[i+1]*3;
            p3[0] = vertices[v3];
            p3[1] = vertices[v3+1];
            p3[2] = vertices[v3+2];

            tmpNormal = ComputeSurfaceNormal (p1, p2, p3);

            normals[v1] = tmpNormal[0];
            normals[v1+1] = tmpNormal[1];
            normals[v1+2] = tmpNormal[2];

            normals[v2] = tmpNormal[0];
            normals[v2+1] = tmpNormal[1];
            normals[v2+2] = tmpNormal[2];

            normals[v3] = tmpNormal[0];
            normals[v3+1] = tmpNormal[1];
            normals[v3+2] = tmpNormal[2];
        }
    }
    if(!isTriangleFan)
    {
        for(GLushort i=0; i<nbIndices; i=i+3)
        {
            v1 = indices[i]*3;
            p1[0] = vertices[v1];
            p1[1] = vertices[v1+1];
            p1[2] = vertices[v1+2];

            v2 = indices[i+1]*3;
            p2[0] = vertices[v2];
            p2[1] = vertices[v2+1];
            p2[2] = vertices[v2+2];

            v3 = indices[i+2]*3;
            p3[0] = vertices[v3];
            p3[1] = vertices[v3+1];
            p3[2] = vertices[v3+2];

            tmpNormal = ComputeSurfaceNormal (p1, p2, p3);

            normals[v1] = tmpNormal[0];
            normals[v1+1] = tmpNormal[1];
            normals[v1+2] = tmpNormal[2];

            normals[v2] = tmpNormal[0];
            normals[v2+1] = tmpNormal[1];
            normals[v2+2] = tmpNormal[2];

            normals[v3] = tmpNormal[0];
            normals[v3+1] = tmpNormal[1];
            normals[v3+2] = tmpNormal[2];
        }
    }
}
