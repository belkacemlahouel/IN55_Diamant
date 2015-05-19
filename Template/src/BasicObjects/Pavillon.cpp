#include "Pavillon.h"


Pavillon::Pavillon()
{

}

Pavillon::Pavillon(float radius, float heigth, float heigthFirstLvl, int complexity)
{
    int i;
    //nb of points at the second level in pavillon.
    int nbPtLvl1 = complexity/2;

    //to begin I just construct the peak and the first level
    int size = 3*(nbPtLvl1+1);
    GLfloat vertices[size];

    //peak
    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    vertices[2] = 0.0f;

    for(i=1; i<=nbPtLvl1;++i)
    {
        int cell = i*3;
        //position on x-axis
        vertices[cell] = radius * cos(i*(2*M_PI/nbPtLvl1));
        //position on y-axis
        vertices[cell+1] = radius * sin(i*(2*M_PI/nbPtLvl1));
        //position on z-axis
        vertices[cell+2] = heigthFirstLvl;

    }
}


Pavillon::~Pavillon()
{

}

/** TODO:
 * adapt to pavillon
 * */
void Pavillon::initVBO()
{
    /* VBOs generation & binding */
   /** glGenBuffers(1, &VertexVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, VertexVBOID);
    glBufferData(GL_ARRAY_BUFFER, verticesArraySize*sizeof(GLfloat), verticesArray, GL_STATIC_DRAW);

    glGenBuffers(1, &ColorVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, ColorVBOID);
    glBufferData(GL_ARRAY_BUFFER, verticesArraySize*sizeof(GLfloat), colorsArray, GL_STATIC_DRAW);

    glGenBuffers(1, &IndicesVBOID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesVBOID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesArraySize*sizeof(GLushort), CubeIndices, GL_STATIC_DRAW);

    hasInitiatedVBO = true;*/
}

/** TODO : Recall initVBO when data changes ?
 * + Adapt the function to pavillon
*/
void Pavillon::drawShape(const char* shader_name)
{
    /* Enable attributes arrays */
    /** GLint positionLocation = glGetAttribLocation(m_Framework->getCurrentShaderId(), "position");
    GLint colorLocation = glGetAttribLocation(m_Framework->getCurrentShaderId(), "color");

    glEnableVertexAttribArray(positionLocation);
    glEnableVertexAttribArray(colorLocation);*/

    /* Draw the cube */
    /** if(!hasInitiatedVBO)
        this->initVBO();*/

    /* Draw the cube */
    /** glBindBuffer(GL_ARRAY_BUFFER, VertexVBOID);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, ColorVBOID);
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesVBOID);
    glDrawElements(GL_TRIANGLES, indicesArraySize, GL_UNSIGNED_SHORT, 0);*/

    /* Disable attributes arrays */
    /** glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(colorLocation);*/
}
