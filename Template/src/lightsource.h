#ifndef LIGHTSOURCE
#define LIGHTSOURCE

#include "Color.h"
#include "Types.h"

class LightSource
{
    public:
        /*
         * Position si posDir.w = 1
         * Direction si posDir.w = 0
         */
        GLfloat *posDir;

        GLfloat *ambient;
        GLfloat *diffuse;
        GLfloat *specular;

        GLfloat constantAttenuation;
        GLfloat linearAttenuation;
        GLfloat quadraticAttenuation;

        GLfloat *spotDirection;
        GLfloat spotCutoff;
        GLfloat spotExponent;


        LightSource(GLfloat posDir[4],
                    GLfloat ambient[4], GLfloat diffuse[4], GLfloat specular[4],
                    GLfloat constantAttenuation, GLfloat linearAttenuation, GLfloat quadraticAttenuation,
                    GLfloat spotDirection[3], GLfloat spotCutoff, GLfloat spotExponent);
};

typedef struct{
     LightSource lights[2];
}LightSources;

#endif // LIGHTSOURCE

