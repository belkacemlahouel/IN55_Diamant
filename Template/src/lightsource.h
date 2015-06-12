#ifndef LIGHTSOURCE
#define LIGHTSOURCE

#include "Color.h"
#include "Types.h"

class LightSource
{
    private:
        GLfloat id;

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

        AbstractFramework* m_Framework = NULL;

    public:
        LightSource(AbstractFramework* fw, GLuint id,
                    GLfloat posDir[4],
                    GLfloat ambient[4], GLfloat diffuse[4], GLfloat specular[4],
                    GLfloat constantAttenuation, GLfloat linearAttenuation, GLfloat quadraticAttenuation,
                    GLfloat spotDirection[3], GLfloat spotCutoff, GLfloat spotExponent);

        void submitLight();
        void updateLight();
};

#endif // LIGHTSOURCE

