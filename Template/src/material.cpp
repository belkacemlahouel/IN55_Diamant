#include "material.h"

Material::Material(AbstractFramework* fw, GLfloat ambient[4], GLfloat diffuse[4], GLfloat specular[4], GLfloat shininess)
{
    this->m_Framework = fw;

    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;

    this->shininess = shininess;

    this->submitMaterial();
}

void Material::submitMaterial()
{
    glUniform4fv(glGetUniformLocation(this->m_Framework->getCurrentShaderId(), "material.ambient"), 1, (GLfloat *) this->ambient);
    glUniform4fv(glGetUniformLocation(this->m_Framework->getCurrentShaderId(), "material.diffuse"), 1, (GLfloat *) this->diffuse);
    glUniform4fv(glGetUniformLocation(this->m_Framework->getCurrentShaderId(), "material.specular"), 1, (GLfloat *) this->specular);

    glUniform1f(glGetUniformLocation(this->m_Framework->getCurrentShaderId(), "material.shininess"), this->shininess);
}
