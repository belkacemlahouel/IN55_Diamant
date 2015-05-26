#include "rondiste.h"

Rondiste::Rondiste()
{

}

Rondiste::Rondiste(float32 radius, float32 pavillonHeight, float32 rondisteHeight, int32 complexity, const GLfloat color[])
{
    int32 cell, i;
    int32 nbPoint = complexity * 3;
    int32 size = nbPoint*3;
    int32 iterations = size/9;
    float32 halfHeight = rondisteHeight/2;

    float32 angle = 2*M_PI/(complexity*2);
    float32 anglePhase1, anglePhase2;

    verticesArray = new GLfloat[size];
    verticesArraySize = size;
    colorsArray = new GLfloat[size];

    for(i=0; i<iterations; ++i)
    {
        cell = i*9;

        anglePhase1 = (i-0.25)*angle;
        anglePhase2 = (i-0.5)*angle;

        //position of the first point
        verticesArray[cell] = radius * cos(anglePhase2);
        verticesArray[cell+1] = pavillonHeight;
        verticesArray[cell+2] = radius * sin(anglePhase2);

        //position of the second point
        verticesArray[cell+3] = radius * cos(anglePhase1);
        verticesArray[cell+4] = pavillonHeight - halfHeight;
        verticesArray[cell+5] = radius * sin(anglePhase1);

        //position of the third point
        verticesArray[cell+6] = radius * cos(anglePhase1);
        verticesArray[cell+7] = pavillonHeight + halfHeight;
        verticesArray[cell+8] = radius * sin(anglePhase1);

        colorsArray[cell]    = color[0];
        colorsArray[cell+1]  = color[1];
        colorsArray[cell+2]  = color[2];
    }

    /* Initialize the array of indices */
    indicesArraySize = 6*complexity;
    indicesArray = new GLushort[indicesArraySize];
    //iterations = ;
    i = 0;
    while(i+5<indicesArraySize)
    {
        indicesArray[i]=i;
        indicesArray[i+1]=i+1;
        indicesArray[i+2]=i+2;
        indicesArray[i+3]=i+1;
        indicesArray[i+4]=i+2;
        indicesArray[i+5]=i;
        // cout << i+5 << endl;
        i+=3;
    }
    //cout << "Size : " <<indicesArraySize << endl;
}


Rondiste::~Rondiste()
{
    delete [] verticesArray;
    delete [] colorsArray;
    delete [] indicesArray;

    glDeleteBuffers(1, &VertexVBOID);
    glDeleteBuffers(1, &ColorVBOID);
    glDeleteBuffers(1, &IndicesVBOID);
}

void Rondiste::initVBO()
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesArraySize*sizeof(GLushort), indicesArray, GL_STATIC_DRAW);

    hasInitiatedVBO = true;
}



void Rondiste::drawShape(const char *shader_name)
{
    /* Enable attributes arrays */
    GLint positionLocation = glGetAttribLocation(m_Framework->getCurrentShaderId(), "position");
    GLint colorLocation = glGetAttribLocation(m_Framework->getCurrentShaderId(), "color");

    glEnableVertexAttribArray(positionLocation);
    glEnableVertexAttribArray(colorLocation);

    /* Initiate the VBO if it has not been done already */
    if(!hasInitiatedVBO)
        this->initVBO();

    /* Draw the pavillon */
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

