#include "table.h"

Table::Table()
{

}


Table::Table(float32 radiusTable, float32 heightCrown, float32 heightPavillon, int32 complexity, const GLfloat color[3])
{
    /* VBO has not been initialized already */
    this->hasInitiatedVBO = false;

    int32 nbFaces = complexity/2;
    int32 nbPoints = nbFaces+1;
    int32 size = nbPoints*3;
    int32 height = heightCrown + heightPavillon;
    float32 angle = 2*M_PI/(nbFaces*2);
    int32 cell, i;
    float32 anglePhase;

    verticesArraySize = size;
    verticesArray = new GLfloat[verticesArraySize];

    indicesArraySize = nbPoints;
    indicesArray = new GLushort[indicesArraySize];

    colorsArraySize = size;
    colorsArray = new GLfloat[colorsArraySize];

    /* Initialization of the first point (center of the table) */
    verticesArray[0] = 0;
    verticesArray[1] = height;
    verticesArray[2] = 0;

    for(i=0; i<nbPoints;++i)
    {
        cell = i*3;
        anglePhase = (i+0.5)*angle*2;

        //x, y and z-positions of the point i
        verticesArray[cell] = radiusTable * cos(anglePhase);
        verticesArray[cell+1] = height;
        verticesArray[cell+2] = radiusTable * sin(anglePhase);

        colorsArray[cell]    = color[0];
        colorsArray[cell+1]  = color[1];
        colorsArray[cell+2]  = color[2];
    }

    for(i=0; i<indicesArraySize; ++i)
    {
        indicesArray[i] = i;
    }

    normalsArray = new GLfloat[verticesArraySize];
    computeNormals(normalsArray, verticesArray, verticesArraySize, indicesArray, indicesArraySize);
}


Table::~Table()
{
    delete [] verticesArray;
    delete [] indicesArray;
    delete [] colorsArray;
    delete [] normalsArray;

    glDeleteBuffers(1, &VerticesVBOID);
    glDeleteBuffers(1, &ColorsVBOID);
    glDeleteBuffers(1, &IndicesVBOID);
    glDeleteBuffers(1, &NormalsVBOID);
}


void Table::initVBO()
{
    /* VBOs generation & binding for the principal faces (big quadrilaterals)*/
    glGenBuffers(1, &VerticesVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, VerticesVBOID);
    glBufferData(GL_ARRAY_BUFFER, verticesArraySize*sizeof(GLfloat), verticesArray, GL_STATIC_DRAW);

    glGenBuffers(1, &ColorsVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, ColorsVBOID);
    glBufferData(GL_ARRAY_BUFFER, colorsArraySize*sizeof(GLfloat), colorsArray, GL_STATIC_DRAW);

    glGenBuffers(1, &IndicesVBOID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesVBOID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesArraySize*sizeof(GLushort), indicesArray, GL_STATIC_DRAW);

    glGenBuffers(1, &NormalsVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, NormalsVBOID);
    glBufferData(GL_ARRAY_BUFFER, verticesArraySize*sizeof(GLfloat), normalsArray, GL_STATIC_DRAW);

    hasInitiatedVBO = true;
}


void Table::drawShape(const char *shader_name)
{
    /* Enable attributes arrays */
    GLint positionLocation = glGetAttribLocation(m_Framework->getCurrentShaderId(), "position");
    GLint colorLocation = glGetAttribLocation(m_Framework->getCurrentShaderId(), "color");
    GLint normalLocation = glGetAttribLocation(m_Framework->getCurrentShaderId(), "normal");

    glEnableVertexAttribArray(positionLocation);
    glEnableVertexAttribArray(colorLocation);
    glEnableVertexAttribArray(normalLocation);

    /* Initiate the VBO if it has not been done already */
    if(!hasInitiatedVBO)
        this->initVBO();

    /* Draw the principal faces of the crown */
    glBindBuffer(GL_ARRAY_BUFFER, VerticesVBOID);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, ColorsVBOID);
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, NormalsVBOID);
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesVBOID);
    glDrawElements(GL_TRIANGLE_FAN, indicesArraySize, GL_UNSIGNED_SHORT, 0);

    /* Disable attributes arrays */
    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(colorLocation);
    glDisableVertexAttribArray(normalLocation);
}
