#include "rondiste.h"

Rondiste::Rondiste()
{

}

Rondiste::Rondiste(float32 radius, float32 pavillonHeight, float32 rondisteHeight, int32 complexity, const GLfloat color[])
{
   /* int32 cell;
    int32 nbPoint = complexity * 3;
    int32 size = nbPoint*3;
    int32 iterations = size/9;
    float32 halfHeight = rondisteHeight/2;

    float32 angle = 2*M_PI/(complexity*2);
    float32 anglePhase1, anglePhase2;

    verticesArray = new GLfloat[size];
    colorsArray = new GLfloat[size];

    for(int32 i=0; i<iterations; ++i)
    {
        cell = i*9;

        anglePhase1 = (i-0.25)*angle;
        anglePhase2 = (i-0.5)*angle;

        //position of the first point
        verticesArray[cell] = radius * cos(anglePhase2);
        verticesArray[cell+1] = pavillonHeight;
        verticesArray[cell+3] = radius * sin(anglePhase2);

        //position of the second point
        verticesArray[cell+4] = radius * cos(anglePhase1);
        verticesArray[cell+5] = pavillonHeight - halfHeight;
        verticesArray[cell+6] = radius * sin(anglePhase1);

        //position of the third point
        verticesArray[cell+7] = radius * cos(anglePhase1);
        verticesArray[cell+8] = pavillonHeight + halfHeight;
        verticesArray[cell+9] = radius * sin(anglePhase1);

        colorsArray[cell]    = color[0];
        colorsArray[cell+1]  = color[1];
        colorsArray[cell+2]  = color[2];
    }*/
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



