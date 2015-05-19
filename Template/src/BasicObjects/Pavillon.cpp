#include "Pavillon.h"

#include <iostream>

Pavillon::Pavillon()
{

}

Pavillon::Pavillon(float radius, float heigth, float heigthFirstLvl, int complexity, const GLfloat color[3])
{
    //nb of points at the second level in pavillon.
    int nbPtLvl1 = complexity/2;

    //to begin I just construct the peak and the first level
    int size = 3*(nbPtLvl1+1);

    pavillonVertices = new GLfloat[size];
    colorsArray = new GLfloat[size];
    pavillonIndices = new GLushort[size/3];

    //peak
    pavillonVertices[0] = 0.0f;
    pavillonVertices[1] = 0.0f;
    pavillonVertices[2] = 0.0f;

    colorsArray[0]  = color[0];
    colorsArray[1]  = color[1];
    colorsArray[2]  = color[2];

    pavillonIndices[0] = 0;

    int cell;
    for(int i=1; i<=nbPtLvl1; i++)
    {
        cell = i*3;

        //position on x-axis
        pavillonVertices[cell] = radius * cos(i*(2*M_PI/nbPtLvl1));
        //position on y-axis
        pavillonVertices[cell+1] = radius * sin(i*(2*M_PI/nbPtLvl1));
        //position on z-axis
        pavillonVertices[cell+2] = heigthFirstLvl;

        colorsArray[cell]    = color[0];
        colorsArray[cell+1]  = color[1];
        colorsArray[cell+2]  = color[2];

        pavillonIndices[i] = i;
    }

    hasInitiatedVBO = false;

    verticesArraySize = size;
    indicesArraySize = size/3;
}


Pavillon::~Pavillon()
{
    delete [] pavillonVertices;
    delete [] colorsArray;
    delete [] pavillonIndices;

    glDeleteBuffers(1, &VertexVBOID);
    glDeleteBuffers(1, &ColorVBOID);
    glDeleteBuffers(1, &IndicesVBOID);
}

void Pavillon::initVBO()
{
    /* VBOs generation & binding */
    glGenBuffers(1, &VertexVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, VertexVBOID);
    glBufferData(GL_ARRAY_BUFFER, verticesArraySize*sizeof(GLfloat), pavillonVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ColorVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, ColorVBOID);
    glBufferData(GL_ARRAY_BUFFER, verticesArraySize*sizeof(GLfloat), colorsArray, GL_STATIC_DRAW);

    glGenBuffers(1, &IndicesVBOID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesVBOID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesArraySize*sizeof(GLushort), pavillonIndices, GL_STATIC_DRAW);

    hasInitiatedVBO = true;
}

void Pavillon::drawShape(const char* shader_name)
{
    /* Enable attributes arrays */
    GLint positionLocation = glGetAttribLocation(m_Framework->getCurrentShaderId(), "position");
    GLint colorLocation = glGetAttribLocation(m_Framework->getCurrentShaderId(), "color");

    glEnableVertexAttribArray(positionLocation);
    glEnableVertexAttribArray(colorLocation);

    /* Draw the pavillon */
    if(!hasInitiatedVBO)
        this->initVBO();

    /* Draw the pavillon */
    glBindBuffer(GL_ARRAY_BUFFER, VertexVBOID);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, ColorVBOID);
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesVBOID);
    glDrawElements(GL_TRIANGLE_FAN, indicesArraySize, GL_UNSIGNED_SHORT, 0);

    /* Disable attributes arrays */
    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(colorLocation);
}
