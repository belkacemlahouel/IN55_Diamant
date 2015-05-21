#include "Pavillon.h"


Pavillon::Pavillon()
{

}

Pavillon::Pavillon(float32 radius, float32 height, float32 heightFirstLvl, int32 complexity, const GLfloat color[3])
{
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

    int32 cell;
    for(int i=1; i<=nbPtLvl1; i++)
    {
        cell = i*3;

        //position on x-axis
        pavillonVertices[cell] = (radius/2) * cos(i*(2*M_PI/nbPtLvl1));
        //position on y-axis
        pavillonVertices[cell+1] = heightFirstLvl;
        //position on z-axis
        pavillonVertices[cell+2] = (radius/2) * sin(i*(2*M_PI/nbPtLvl1));

        colorsArray[cell]    = color[0];
        colorsArray[cell+1]  = color[1];
        colorsArray[cell+2]  = color[2];

        pavillonIndices[i] = i;
    }
    pavillonIndices[nbPtLvl1+1]=1;
    hasInitiatedVBO = false;

    verticesArraySize = size;
    indicesArraySize = size/3+1;

    /*-------------Create the last level--------------------*/
    createSecondLvl(nbPtLvl1, radius, height, color);
}

/**
 * Function used to initialize the different tables for the second level.
 * @brief createSecondLvl
 * @param nbPtLvl1
 * @param radius
 * @param height
 * @param color
 */
void Pavillon::createSecondLvl(int32 nbPtLvl1, float32 radius, float32 height,  const GLfloat color[3])
{
    int32 size = nbPtLvl1*6;
    int32 iterations, i;
    int32 start;
    int32 cell, cellFirstLvl, indice;
    pavillonQuadLastLvlVertices = new GLfloat[size];
    pavillonTrianglesLastLvlVertices = new GLfloat[size];
    colorsLastLvlArray = new GLfloat[size];
    verticesQuadLastLvlArraySize = size;
    verticesTrianglesLastLvlArraySize = size;

    /* Create points for the little triangles and the color array*/
    for(i=0; i<nbPtLvl1; ++i)
    {
        cell = i*3;
        //position on x-axis of the new point
        pavillonTrianglesLastLvlVertices[cell] = radius * cos(i*(2*M_PI/nbPtLvl1));
        //position on y-axis of the new point
        pavillonTrianglesLastLvlVertices[cell+1] = height;
        //position on z-axis of the new point
        pavillonTrianglesLastLvlVertices[cell+2] = radius * sin(i*(2*M_PI/nbPtLvl1));

        colorsLastLvlArray[cell]    = color[0];
        colorsLastLvlArray[cell+1]  = color[1];
        colorsLastLvlArray[cell+2]  = color[2];
    }

    /* Create points for the quadrilaterals*/
    for(int32 j=0; j<nbPtLvl1; ++j)
    {
        /* delay (in angle) of points is made by add j*(2*M_PI/nbPtLvl1)/2 */
        cell = j*3;
        //position on x-axis of the new point
        pavillonQuadLastLvlVertices[cell] = radius * cos(j*(2*M_PI/nbPtLvl1)+j*(2*M_PI/nbPtLvl1)/2);
        //position on y-axis of the new point
        pavillonQuadLastLvlVertices[cell+1] = height;
        //position on z-axis of the new point
        pavillonQuadLastLvlVertices[cell+2] = radius * sin(j*(2*M_PI/nbPtLvl1)+j*(2*M_PI/nbPtLvl1)/2);
    }

    /* Catch the points of the first level*/
    iterations = nbPtLvl1*2;
    cellFirstLvl=2;

    for(int32 k=nbPtLvl1; k<iterations; ++k)
    {
        cell = k*3;
        ++cellFirstLvl;
        //position on x-axis of the new point
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

        /*colorsLastLvlArray[cell] = color[0];
        colorsLastLvlArray[cell+1] = color[1];
        colorsLastLvlArray[cell+2] = color[2];*/
        colorsLastLvlArray[cell] = 0.5;
        colorsLastLvlArray[cell+1] = 0.3;
        colorsLastLvlArray[cell+2] = 0.0;

    }

    /* Create the tables of indices */
    size = nbPtLvl1*3;
    indicesLastLvlTrianglesIndices = new GLushort[size*2];
    indicesLastLvlQuadIndices = new GLushort[size];
    indicesLastLvlArraySize = size;

    for(i=0;i<nbPtLvl1;++i)
    {
        cell=i*3;
        indicesLastLvlQuadIndices[cell]=i;
        cout << i << "-";
        indice = nbPtLvl1+i;
        indicesLastLvlQuadIndices[cell+1]=indice;
        cout << indice << "-";
        /* If indice+1 is superior to nbPtLvl1*2, it means that we gonna go out from the vertices table, we must continue at its beginning */
        if((indice+1) >= (nbPtLvl1*2))
        {
            indicesLastLvlQuadIndices[cell+2]=nbPtLvl1;
            cout << nbPtLvl1;
        }
        else
        {
            indicesLastLvlQuadIndices[cell+2]=indice+1;
            cout << indice+1 << "-";
        }
    }
}




Pavillon::~Pavillon()
{
    delete [] pavillonVertices;
    delete [] colorsArray;
    delete [] pavillonIndices;

    delete [] pavillonQuadLastLvlVertices;
    delete [] pavillonTrianglesLastLvlVertices;
    delete [] colorsLastLvlArray;
    delete [] indicesLastLvlTrianglesIndices;
    delete [] indicesLastLvlQuadIndices;

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

    /* VBOs generation & binding for quad of the second level*/
    glGenBuffers(1, &VertexQuadVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, VertexQuadVBOID);
    glBufferData(GL_ARRAY_BUFFER, verticesQuadLastLvlArraySize*sizeof(GLfloat), pavillonQuadLastLvlVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ColorQuadVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, ColorQuadVBOID);
    glBufferData(GL_ARRAY_BUFFER, verticesQuadLastLvlArraySize*sizeof(GLfloat), colorsLastLvlArray, GL_STATIC_DRAW);

    glGenBuffers(1, &IndicesQuadVBOID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesQuadVBOID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLastLvlArraySize*sizeof(GLushort), indicesLastLvlQuadIndices, GL_STATIC_DRAW);

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

    /* Draw the quadrilaterals of the "pavillon" */
    glBindBuffer(GL_ARRAY_BUFFER, VertexQuadVBOID);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, ColorQuadVBOID);
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesQuadVBOID);
    glDrawElements(GL_TRIANGLES, indicesArraySize, GL_UNSIGNED_SHORT, 0);

    /* Disable attributes arrays */
    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(colorLocation);
}
