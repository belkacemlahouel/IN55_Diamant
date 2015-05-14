#include "Cube.h"
#include "Types.h"
#include <iostream>

static const GLfloat CubeVertices_Duplicated[] =
{
    /* Front */
    0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 0.0f,

    /* Back */
    0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f,

    /* Bottom */
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,

    /* Top */
    0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f,

    /* Right */
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f,

    /* Left */
    0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 0.0f
};
static const GLfloat CubeVertices[] =
{
    /* Front */
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,

    /* Back */
    0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f
};
static const GLushort CubeIndices[] =
{
    /* Front */
    0, 1, 2,
    1, 2, 3,

    /* Back */
    5, 7, 4,
    4, 7, 6,

    /* Bottom */
    4, 0, 5,
    5, 0, 1,

    /* Top */
    2, 6, 7,
    7, 6, 3,

    /* Right */
    1, 3, 5,
    5, 3, 7,

    /* Left */
    4, 6, 0,
    0, 6, 2
};

Cube::Cube(GLfloat cubeLength, const GLfloat cubeColor[3])
{
    this->length = length;

    /* Adjust size & color */
    int currentId;
    for(int i=0; i<8; i++)
    {
        currentId = i*3;
        verticesArray[currentId]   = CubeVertices[currentId]*cubeLength;
        verticesArray[currentId+1] = CubeVertices[currentId+1]*cubeLength;
        verticesArray[currentId+2] = CubeVertices[currentId+2]*cubeLength;

        colorsArray[currentId]    = cubeColor[0];
        colorsArray[currentId+1]  = cubeColor[1];
        colorsArray[currentId+2]  = cubeColor[2];
    }

    hasInitiatedVBO = false;

    verticesArraySize = sizeof(CubeVertices)/sizeof(GLfloat);
    indicesArraySize = sizeof(CubeIndices)/sizeof(GLushort);
}
Cube::~Cube()
{
    glDeleteBuffers(1, &VertexVBOID);
    glDeleteBuffers(1, &ColorVBOID);
    glDeleteBuffers(1, &IndicesVBOID);
}

void Cube::initVBO()
{
    /* VBOs generation & binding */
    glGenBuffers(1, &VertexVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, VertexVBOID);
    glBufferData(GL_ARRAY_BUFFER, verticesArraySize*sizeof(GLfloat), verticesArray, GL_STATIC_DRAW);

    glGenBuffers(1, &ColorVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, ColorVBOID);
    glBufferData(GL_ARRAY_BUFFER, verticesArraySize*sizeof(GLfloat), colorsArray, GL_STATIC_DRAW);

    glGenBuffers(1, &IndicesVBOID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesVBOID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesArraySize*sizeof(GLushort), CubeIndices, GL_STATIC_DRAW);

    hasInitiatedVBO = true;
}

/* TODO : Recall initVBO when data changes ? */
void Cube::drawShape(const char* shader_name)
{
    /* Enable attributes arrays */
    GLint positionLocation = glGetAttribLocation(m_Framework->getCurrentShaderId(), "position");
    GLint colorLocation = glGetAttribLocation(m_Framework->getCurrentShaderId(), "color");

    glEnableVertexAttribArray(positionLocation);
    glEnableVertexAttribArray(colorLocation);

    /* Draw the cube */
    if(!hasInitiatedVBO)
        this->initVBO();

    /* Draw the cube */
    glBindBuffer(GL_ARRAY_BUFFER, VertexVBOID);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, ColorVBOID);
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesVBOID);
    glDrawElements(GL_TRIANGLES, indicesArraySize, GL_UNSIGNED_SHORT, 0);

    /* Disable attributes arrays */
    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(colorLocation);
}
