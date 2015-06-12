#include "lightsource.h"

LightSource::LightSource(AbstractFramework* fw, GLuint id,
                         GLfloat posDir[4],
                         GLfloat ambient[4], GLfloat diffuse[4], GLfloat specular[4],
                         GLfloat constantAttenuation, GLfloat linearAttenuation, GLfloat quadraticAttenuation,
                         GLfloat spotDirection[3], GLfloat spotCutoff, GLfloat spotExponent)
{
    this->m_Framework = fw;

    this->id = id;

    this->posDir = posDir;

    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;

    this->constantAttenuation = constantAttenuation;
    this->linearAttenuation = linearAttenuation;
    this->quadraticAttenuation = quadraticAttenuation;

    this->spotDirection = spotDirection;
    this->spotCutoff = spotCutoff;
    this->spotExponent = spotExponent;

    this->submitLight();
    this->updateLight();
}

void LightSource::submitLight()
{
    glUniform4fv(glGetUniformLocation(m_Framework->getCurrentShaderId(), "light.ambient"), 1, (GLfloat *) this->ambient);
    glUniform4fv(glGetUniformLocation(m_Framework->getCurrentShaderId(), "light.diffuse"), 1, (GLfloat *) this->diffuse);
    glUniform4fv(glGetUniformLocation(m_Framework->getCurrentShaderId(), "light.specular"), 1, (GLfloat *) this->specular);

    glUniform1f(glGetUniformLocation(m_Framework->getCurrentShaderId(), "light.constantAttenuation"), this->constantAttenuation);
    glUniform1f(glGetUniformLocation(m_Framework->getCurrentShaderId(), "light.linearAttenuation"), this->linearAttenuation);
    glUniform1f(glGetUniformLocation(m_Framework->getCurrentShaderId(), "light.quadraticAttenuation"), this->quadraticAttenuation);

    glUniform3fv(glGetUniformLocation(m_Framework->getCurrentShaderId(), "light.spotDirection"), 1, (GLfloat *) this->spotDirection);
    glUniform1f(glGetUniformLocation(m_Framework->getCurrentShaderId(), "light.spotCutoff"), this->spotCutoff);
    glUniform1f(glGetUniformLocation(m_Framework->getCurrentShaderId(), "light.spotExponent"), this->spotExponent);
}

void LightSource::updateLight()
{
    glUniform4fv(glGetUniformLocation(m_Framework->getCurrentShaderId(), "light.posDir"), 1, (GLfloat *) this->posDir);
}
