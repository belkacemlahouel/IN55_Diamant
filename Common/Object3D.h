#ifndef Object3D_h
#define Object3D_h

#include "AbstractFramework.h"


class Object3D
{
    public:
        ~Object3D();
        static void setFramework(AbstractFramework*);

        void draw();
        void draw(const char* shader_name);

    protected:
        static AbstractFramework* m_Framework;

        virtual void drawShape(const char* shader_name = NULL) = 0;

        void computeNormals(GLfloat *normals, GLfloat *vertices, GLushort nbVertices, GLushort *indices, GLushort nbIndices, bool isTriangleFan = false);
        bool setAlpha(GLfloat alpha);

    private:
        GLfloat* ComputeSurfaceNormal (GLfloat p1[3], GLfloat p2[3], GLfloat p3[3]);

};

#endif
