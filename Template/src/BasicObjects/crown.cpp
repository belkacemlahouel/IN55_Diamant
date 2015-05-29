#include "crown.h"

Crown::Crown()
{

}


Crown::Crown(float32 radius, float32 table, float32 crownHeight, float32 rondisteHeight,float32 pavillonHeight, float32 lvlCrownHeight, int32 complexity, const GLfloat color[])
{
    /* VBO has not been initialized already */
    this->hasInitiatedVBO = false;

    int32 cell, i;
    int32 nbFaces = complexity/4;
    int32 nbPoint = nbFaces * 3;
    int32 size = nbPoint*3;
    int32 iterations = size/9;
    //float32 halfHeight = 2.0;
    float32 angle = 2*M_PI/(nbFaces*2);
    float32 anglePhase1, anglePhase2;
    float32 radiusIntermediateLvl = radius*2/3;
    //cout << "Radius : " << radiusIntermediateLvl << " Angle :"<<angle;
    float32 height = pavillonHeight+lvlCrownHeight;

    verticesPrincipalFacesUpArray = new GLfloat[size];
    verticesPrincipalArraySize = size;
    colorsPrincipalArray = new GLfloat[size];

    for(i=0; i<iterations; ++i)
    {
        cell = i*9;

        anglePhase2 = (i-0.5)*angle*2;
        anglePhase1 = (i)*angle*2;

        //position of the first point
        verticesPrincipalFacesUpArray[cell] = radiusIntermediateLvl * cos(anglePhase2);
        verticesPrincipalFacesUpArray[cell+1] = height;
        verticesPrincipalFacesUpArray[cell+2] = radiusIntermediateLvl * sin(anglePhase2);
        //cout <<verticesPrincipalFacesUpArray[cell]<<"&"<<verticesPrincipalFacesUpArray[cell+2]<<endl;
        //position of the second point
        verticesPrincipalFacesUpArray[cell+3] = radius * cos(anglePhase1);
        verticesPrincipalFacesUpArray[cell+4] = pavillonHeight;
        verticesPrincipalFacesUpArray[cell+5] = radius * sin(anglePhase1);

        //position of the third point
        verticesPrincipalFacesUpArray[cell+6] = radius * cos(anglePhase1);
        verticesPrincipalFacesUpArray[cell+7] = pavillonHeight + crownHeight;
        verticesPrincipalFacesUpArray[cell+8] = radius * sin(anglePhase1);

        colorsPrincipalArray[cell]    = color[0];
        colorsPrincipalArray[cell+1]  = color[1];
        colorsPrincipalArray[cell+2]  = color[2];
    }

    /* Initialize the array of indices */
    //Each faces have 2 triangles of 3 points.
    indicesPrincipalArraySize = nbFaces*6;
    indicesPrincipalArray = new GLushort[indicesPrincipalArraySize];

    i = 0;
    cell = 0;
    while(cell<indicesPrincipalArraySize)
    {
        indicesPrincipalArray[cell]=i;
        indicesPrincipalArray[cell+1]=i+1;
        indicesPrincipalArray[cell+2]=i+2;
        indicesPrincipalArray[cell+3]=i+1;
        indicesPrincipalArray[cell+4]=i+2;
        indicesPrincipalArray[cell+5]=i+3;
        cell+=6;
        i+=3;
    }

    /* Correction of a wrong face. */
    indicesPrincipalArray[indicesPrincipalArraySize-1]=0;
}


Crown::~Crown()
{
    delete [] verticesPrincipalFacesUpArray;
    delete [] verticesLittleFacesUpArray;

    delete [] indicesPrincipalArray;
    delete [] indicesLittleFacesArray;

    delete [] colorsPrincipalArray;
    delete [] colorsLittleFacesArray;

    glDeleteBuffers(1, &VertexVBOID);
    glDeleteBuffers(1, &ColorVBOID);
    glDeleteBuffers(1, &IndicesVBOID);
}


/**
 * @brief Crown::initVBO
 * Initialize the vertex buffer
 */
void Crown::initVBO()
{
    /* VBOs generation & binding for quad of the second level*/
    glGenBuffers(1, &VertexVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, VertexVBOID);
    glBufferData(GL_ARRAY_BUFFER, verticesPrincipalArraySize*sizeof(GLfloat), verticesPrincipalFacesUpArray, GL_STATIC_DRAW);

    glGenBuffers(1, &ColorVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, ColorVBOID);
    glBufferData(GL_ARRAY_BUFFER, colorsPrincipalArraySize*sizeof(GLfloat), colorsPrincipalArray, GL_STATIC_DRAW);

    glGenBuffers(1, &IndicesVBOID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesVBOID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesPrincipalArraySize*sizeof(GLushort), indicesPrincipalArray, GL_STATIC_DRAW);

    hasInitiatedVBO = true;
}


/**
 * @brief Crown::drawShape
 * Draw the crown of a diamond
 * @param shader_name
 */
void Crown::drawShape(const char *shader_name)
{
    /* Enable attributes arrays */
    GLint positionLocation = glGetAttribLocation(m_Framework->getCurrentShaderId(), "position");
    GLint colorLocation = glGetAttribLocation(m_Framework->getCurrentShaderId(), "color");

    glEnableVertexAttribArray(positionLocation);
    glEnableVertexAttribArray(colorLocation);

    /* Initiate the VBO if it has not been done already */
    if(!hasInitiatedVBO)
        this->initVBO();

    /* Draw the principal faces of the crown */
    glBindBuffer(GL_ARRAY_BUFFER, VertexVBOID);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, ColorVBOID);
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesVBOID);
    glDrawElements(GL_TRIANGLES, indicesPrincipalArraySize, GL_UNSIGNED_SHORT, 0);

    /* Disable attributes arrays */
    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(colorLocation);
}
