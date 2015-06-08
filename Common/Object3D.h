#ifndef Object3D_h
#define Object3D_h

#include "AbstractFramework.h"


class Object3D
{
    public:
        ~Object3D();
        static void setFramework(AbstractFramework*);

    public:
        void draw();
        void draw(const char* shader_name);
        GLfloat* ComputeSurfaceNormal (GLfloat p1[3], GLfloat p2[3], GLfloat p3[3]);

    protected:
        virtual void drawShape(const char* shader_name = NULL) = 0;
        bool setAlpha(GLfloat alpha);


    protected:
        static AbstractFramework* m_Framework;
};

#endif
