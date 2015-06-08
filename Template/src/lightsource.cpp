#include "lightsource.h"

LightSource::LightSource(GLfloat posDir[4],
                         GLfloat ambient[4], GLfloat diffuse[4], GLfloat specular[4],
                         GLfloat constantAttenuation, GLfloat linearAttenuation, GLfloat quadraticAttenuation,
                         GLfloat spotDirection[3], GLfloat spotCutoff, GLfloat spotExponent)
{
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
}
