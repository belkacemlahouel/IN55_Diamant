#include "material.h"

Material::Material(GLfloat ambient[4], GLfloat diffuse[4], GLfloat specular[4], GLfloat shininess)
{
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;

    this->shininess = shininess;
}
