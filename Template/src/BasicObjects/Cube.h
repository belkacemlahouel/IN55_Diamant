#ifndef CUBE_H
#define CUBE_H

#include "Object3D.h"

class Cube : public Object3D
{
    public:
        Cube(float cubeLength, const GLfloat cubeColor[3]);
        ~Cube();

    protected:
        void initVBO();
        void drawShape(const char* shader_name);

    private:
        GLfloat length;
        GLushort verticesArraySize;
        GLushort indicesArraySize;

        GLfloat verticesArray[8*3];
        GLfloat colorsArray[8*3];

        GLuint VertexVBOID;
        GLuint ColorVBOID;
        GLuint IndicesVBOID;

        bool hasInitiatedVBO;
};

#endif // CUBE_H
