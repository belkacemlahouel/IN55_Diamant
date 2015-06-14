#include "Pavillon.h"


Pavillon::Pavillon()
{

}

Pavillon::Pavillon(float32 radius, float32 totalHeight, float32 firstLevelHeight, int32 complexity, float32 rondiste, const GLfloat color[3])
{
    /* VBO has not been initialized already */
    this->hasInitiatedVBO = false;

    //nb of points at the second level in pavillon.
    int32 nbPtLvl1 = complexity/2;

    //to begin I just construct the peak and the first level
    int32 size = 3*(nbPtLvl1+1);

    pavillonVertices = new GLfloat[size];
    colorsArray = new GLfloat[size];
    pavillonIndices = new GLushort[(size/3)+1];

    //peak
    pavillonVertices[0] = 0.0f;
    pavillonVertices[1] = 0.0f;
    pavillonVertices[2] = 0.0f;

    colorsArray[0]  = color[0];
    colorsArray[1]  = color[1];
    colorsArray[2]  = color[2];

    pavillonIndices[0] = 0;

    float32 halfRadius = radius*0.5f;
    float32 angle = 2*M_PI/nbPtLvl1;

    int32 cell;
    float tmpAngle;
    for(int i=1; i<=nbPtLvl1; i++)
    {
        cell = i*3;
        tmpAngle = (i-1)*angle;

        //position on x-axis
        pavillonVertices[cell] = halfRadius * cos(tmpAngle);
        //position on y-axis
        pavillonVertices[cell+1] = firstLevelHeight;
        //position on z-axis
        pavillonVertices[cell+2] = halfRadius * sin(tmpAngle);

        colorsArray[cell]    = color[0];
        colorsArray[cell+1]  = color[1];
        colorsArray[cell+2]  = color[2];

        pavillonIndices[i] = i;
    }

    pavillonIndices[nbPtLvl1+1]=1;

    verticesArraySize = size;
    indicesArraySize = (size/3)+1;

    /*-------------Create the last level--------------------*/
    float32 deltaHeight = rondiste/2;
    createSecondLvl(nbPtLvl1, radius, totalHeight, deltaHeight, color);

    pavillonNormals = new GLfloat[verticesArraySize];
    computeNormals(pavillonNormals, pavillonVertices, verticesArraySize, pavillonIndices, indicesArraySize, true);

    normalsQuadLastLvlVertices = new GLfloat[verticesQuadLastLvlArraySize];
    computeNormals(normalsQuadLastLvlVertices, pavillonQuadLastLvlVertices, verticesQuadLastLvlArraySize, indicesLastLvlQuadIndices, indicesQuadLastLvlArraySize);

    normalsTrianglesLastLvlVertices = new GLfloat[verticesTrianglesLastLvlArraySize];
    computeNormals(normalsTrianglesLastLvlVertices, pavillonTrianglesLastLvlVertices, verticesTrianglesLastLvlArraySize, indicesLastLvlTrianglesIndices, indicesTrianglesLastLvlArraySize-6);
}

/**
 * Function used to initialize the different tables for the second level.
 * @brief createSecondLvl
 * @param nbPtLvl1
 * @param radius
 * @param height
 * @param color
 */
void Pavillon::createSecondLvl(int32 nbPtLvl1, float32 radius, float32 height, float32 deltaHeight, const GLfloat color[3])
{
    int32 size = nbPtLvl1*6;
    int32 iterations, i;
    int32 start;
    int32 cell, cellFirstLvl, indice;
    GLfloat* verticeSaver = new GLfloat[nbPtLvl1*3];

    pavillonQuadLastLvlVertices = new GLfloat[size];
    pavillonTrianglesLastLvlVertices = new GLfloat[size+nbPtLvl1*3];
    colorsQuadLastLvlArray = new GLfloat[size];
    colorsTrianglesLastLvlArray = new GLfloat[size+nbPtLvl1*3];

    verticesQuadLastLvlArraySize = size;
    verticesTrianglesLastLvlArraySize = nbPtLvl1*9;

    /* Create points for the little triangles, the upper triangles of the quadrilaterals and the color array*/
    float32 angle = 2*M_PI/nbPtLvl1;
    float32 quadAngle, trianglesAngle;

    for(i=0; i<nbPtLvl1; ++i)
    {
        cell = i*3;
        start = start+i*3;

        quadAngle = (i+0.5)*angle;
        //trianglesAngle = quadAngle - 0.5*angle;
        trianglesAngle = i*(2*M_PI/nbPtLvl1);

        //position on x-axis of the new point
        pavillonQuadLastLvlVertices[cell] = radius * cos(quadAngle);
        pavillonTrianglesLastLvlVertices[cell] = radius * cos(trianglesAngle);
        verticeSaver[cell] = pavillonQuadLastLvlVertices[cell];

        //position on y-axis of the new point
        pavillonQuadLastLvlVertices[cell+1] = height;
        pavillonTrianglesLastLvlVertices[cell+1] = height-deltaHeight; /*Point is less higher to fit with the "rondiste" */
        verticeSaver[cell+1] = height;

        //position on z-axis of the new point
        pavillonQuadLastLvlVertices[cell+2] = radius * sin(quadAngle);
        pavillonTrianglesLastLvlVertices[cell+2] = radius * sin(trianglesAngle);
        verticeSaver[cell+2] = pavillonQuadLastLvlVertices[cell+2];

        colorsQuadLastLvlArray[cell] = color[0];
        colorsQuadLastLvlArray[cell+1] = color[1];
        colorsQuadLastLvlArray[cell+2] = color[2];

        colorsTrianglesLastLvlArray[cell] = color[0];
        colorsTrianglesLastLvlArray[cell+1] = color[1];
        colorsTrianglesLastLvlArray[cell+2] = color[2];
    }

    /* Catch the points of the first level*/
    iterations = nbPtLvl1*2;
    cellFirstLvl=2;

    for(int32 k=nbPtLvl1; k<iterations; ++k)
    {
        cell = k*3;

        //position on x-axis of the new point
        ++cellFirstLvl;
        pavillonQuadLastLvlVertices[cell] = pavillonVertices[cellFirstLvl];
        pavillonTrianglesLastLvlVertices[cell] = pavillonVertices[cellFirstLvl];

        //position on y-axis of the new point
        ++cellFirstLvl;
        pavillonQuadLastLvlVertices[cell+1] = pavillonVertices[cellFirstLvl];
        pavillonTrianglesLastLvlVertices[cell+1] = pavillonVertices[cellFirstLvl];

        //position on z-axis of the new point
        ++cellFirstLvl;
        pavillonQuadLastLvlVertices[cell+2] = pavillonVertices[cellFirstLvl];
        pavillonTrianglesLastLvlVertices[cell+2] = pavillonVertices[cellFirstLvl];

        colorsQuadLastLvlArray[cell] = color[0];
        colorsQuadLastLvlArray[cell+1] = color[1];
        colorsQuadLastLvlArray[cell+2] = color[2];

        colorsTrianglesLastLvlArray[cell] = color[0];
        colorsTrianglesLastLvlArray[cell+1] = color[1];
        colorsTrianglesLastLvlArray[cell+2] = color[2];
    }

    /* Put vertice of the qudrialterals in the table of vertice of the triangles. */
    int32 num=0;
    for(int32 k=nbPtLvl1*6; k<nbPtLvl1*9; k=k+3)
    {
        pavillonTrianglesLastLvlVertices[k]=verticeSaver[num];
        pavillonTrianglesLastLvlVertices[k+1]=verticeSaver[num+1];
        pavillonTrianglesLastLvlVertices[k+2]=verticeSaver[num+2];

        colorsTrianglesLastLvlArray[k] = color[0];
        colorsTrianglesLastLvlArray[k+1] = color[1];
        colorsTrianglesLastLvlArray[k+2] = color[2];

        num = num+3;
    }

    /* Create the tables of indices */
    size = nbPtLvl1*3;
    indicesLastLvlTrianglesIndices = new GLushort[(size+3)*2];
    indicesLastLvlQuadIndices = new GLushort[size];
    indicesQuadLastLvlArraySize = size;
    indicesTrianglesLastLvlArraySize = (size+3)*2;

    /* Create indices for the little triangles */
    for (i=0; i<nbPtLvl1; ++i)
    {
        cell = i*3;
        indicesLastLvlTrianglesIndices[cell]=i;
        indicesLastLvlTrianglesIndices[cell+1]=nbPtLvl1+i;
        indicesLastLvlTrianglesIndices[cell+2]=nbPtLvl1*2+i;
    }

    for (i=0; i<nbPtLvl1; ++i)
    {
        cell = nbPtLvl1*3 + i*3;
        indicesLastLvlTrianglesIndices[cell]=i;
        indicesLastLvlTrianglesIndices[cell+1]=nbPtLvl1+i;
        if(i!=0)
        {
            indicesLastLvlTrianglesIndices[cell+2]=nbPtLvl1*2+(i-1);
        }
        else
        {
            indicesLastLvlTrianglesIndices[cell+2]=nbPtLvl1*2+(nbPtLvl1-1);
        }
    }

    /* Build the table of indices fo the upper triangles of the quadrilaterals */

    for(i=0;i<nbPtLvl1;++i)
    {
        cell=i*3;
        indicesLastLvlQuadIndices[cell]=i;

        indice = nbPtLvl1+i;
        indicesLastLvlQuadIndices[cell+1]=indice;

        /* If indice+1 is superior to nbPtLvl1*2, it means that we gonna go out from the vertices table,
         * we must continue at its beginning */
        if((indice+1) >= (nbPtLvl1*2))
        {
            indicesLastLvlQuadIndices[cell+2]=nbPtLvl1;
        }
        else
        {
            indicesLastLvlQuadIndices[cell+2]=indice+1;
        }
    }
}

Pavillon::~Pavillon()
{
    delete [] pavillonVertices;
    delete [] colorsArray;
    delete [] pavillonIndices;
    delete [] pavillonNormals;

    delete [] pavillonQuadLastLvlVertices;
    delete [] colorsQuadLastLvlArray;
    delete [] indicesLastLvlQuadIndices;
    delete [] normalsQuadLastLvlVertices;

    delete [] pavillonTrianglesLastLvlVertices;
    delete [] colorsTrianglesLastLvlArray;
    delete [] indicesLastLvlTrianglesIndices;
    delete [] normalsTrianglesLastLvlVertices;

    glDeleteBuffers(1, &VertexVBOID);
    glDeleteBuffers(1, &ColorVBOID);
    glDeleteBuffers(1, &IndicesVBOID);
    glDeleteBuffers(1, &NormalsVBOID);

    glDeleteBuffers(1, &VertexQuadVBOID);
    glDeleteBuffers(1, &ColorQuadVBOID);
    glDeleteBuffers(1, &IndicesQuadVBOID);
    glDeleteBuffers(1, &NormalsQuadVBOID);

    glDeleteBuffers(1, &VertexTrianglesVBOID);
    glDeleteBuffers(1, &ColorTrianglesVBOID);
    glDeleteBuffers(1, &IndicesTrianglesVBOID);
    glDeleteBuffers(1, &NormalsTrianglesVBOID);
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

    glGenBuffers(1, &NormalsVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, NormalsVBOID);
    glBufferData(GL_ARRAY_BUFFER, verticesArraySize*sizeof(GLfloat), pavillonNormals, GL_STATIC_DRAW);

    /* VBOs generation & binding for quad of the second level*/
    glGenBuffers(1, &VertexQuadVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, VertexQuadVBOID);
    glBufferData(GL_ARRAY_BUFFER, verticesQuadLastLvlArraySize*sizeof(GLfloat), pavillonQuadLastLvlVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ColorQuadVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, ColorQuadVBOID);
    glBufferData(GL_ARRAY_BUFFER, verticesQuadLastLvlArraySize*sizeof(GLfloat), colorsQuadLastLvlArray, GL_STATIC_DRAW);

    glGenBuffers(1, &IndicesQuadVBOID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesQuadVBOID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesQuadLastLvlArraySize*sizeof(GLushort), indicesLastLvlQuadIndices, GL_STATIC_DRAW);

    glGenBuffers(1, &NormalsQuadVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, NormalsVBOID);
    glBufferData(GL_ARRAY_BUFFER, verticesQuadLastLvlArraySize*sizeof(GLfloat), normalsQuadLastLvlVertices, GL_STATIC_DRAW);


    glGenBuffers(1, &VertexTrianglesVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, VertexTrianglesVBOID);
    glBufferData(GL_ARRAY_BUFFER, verticesTrianglesLastLvlArraySize*sizeof(GLfloat), pavillonTrianglesLastLvlVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ColorTrianglesVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, ColorTrianglesVBOID);
    glBufferData(GL_ARRAY_BUFFER, verticesTrianglesLastLvlArraySize*sizeof(GLfloat), colorsTrianglesLastLvlArray, GL_STATIC_DRAW);

    glGenBuffers(1, &IndicesTrianglesVBOID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesTrianglesVBOID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesTrianglesLastLvlArraySize*sizeof(GLushort), indicesLastLvlTrianglesIndices, GL_STATIC_DRAW);

    glGenBuffers(1, &NormalsTrianglesVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, NormalsTrianglesVBOID);
    glBufferData(GL_ARRAY_BUFFER, verticesTrianglesLastLvlArraySize*sizeof(GLfloat), normalsTrianglesLastLvlVertices, GL_STATIC_DRAW);

    hasInitiatedVBO = true;
}

void Pavillon::drawShape(const char* shader_name)
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

    /* Draw the pavillon */
    glBindBuffer(GL_ARRAY_BUFFER, VertexVBOID);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, ColorVBOID);
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, NormalsVBOID);
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesVBOID);
    glDrawElements(GL_TRIANGLE_FAN, indicesArraySize, GL_UNSIGNED_SHORT, 0);

    /* Draw the quadrilaterals of the "pavillon" */
    glBindBuffer(GL_ARRAY_BUFFER, VertexQuadVBOID);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, ColorQuadVBOID);
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, NormalsQuadVBOID);
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesQuadVBOID);
    glDrawElements(GL_TRIANGLES, indicesQuadLastLvlArraySize, GL_UNSIGNED_SHORT, 0);

    /* Draw the triangles of the "pavillon" */
    /*glBindBuffer(GL_ARRAY_BUFFER, VertexTrianglesVBOID);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, ColorTrianglesVBOID);
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, NormalsTrianglesVBOID);
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesTrianglesVBOID);
    glDrawElements(GL_TRIANGLES, indicesTrianglesLastLvlArraySize, GL_UNSIGNED_SHORT, 0);*/

    /* Disable attributes arrays */
    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(colorLocation);
    glDisableVertexAttribArray(normalLocation);
}
