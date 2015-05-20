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
        pavillonVertices[cell+1] = (radius/2) * sin(i*(2*M_PI/nbPtLvl1));
        //position on z-axis
        pavillonVertices[cell+2] = heightFirstLvl;

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
        buildQuadrilateral(nbPtLvl1, radius, height, color);
}


/**
 * Create the quadrilaterals in the second level.
 * @brief createSecondLvl
 * @param nbPtLvl1
 * @param radius
 * @param height
 * @param color
 */
void Pavillon::buildQuadrilateral(int32 nbPtLvl1, float32 radius, float32 height,  const GLfloat color[3])
{
        int32 size = nbPtLvl1*9;
        pavillonLastLvlVertices = new GLfloat[size];
        colorsLastLvlArray = new GLfloat[size];
        pavillonLastLvlIndices = new GLushort[(size/3)];
        int32 j = 0;
        int32 indice = 0;
        int32 oldIndice = 0;
        int32 cell = j;
        while(j<nbPtLvl1)
        {
            //position on x-axis of the new point
            pavillonLastLvlVertices[cell] = radius * cos(j*(2*M_PI/nbPtLvl1));
            //position on y-axis of the new point
            pavillonLastLvlVertices[cell+1] = radius * sin(j*(2*M_PI/nbPtLvl1));
            //position on z-axis of the new point
            pavillonLastLvlVertices[cell+2] = height;

            colorsLastLvlArray[cell]    = color[0];
            colorsLastLvlArray[cell+1]  = color[1];
            colorsLastLvlArray[cell+2]  = color[2];

            pavillonLastLvlIndices[indice] = indice;
            ++indice;

            /* Catch vertice from first level to create triangles */
            /* First point */
            cell+=3;
            cout << "old i first : "<<oldIndice;
            pavillonLastLvlVertices[cell] = pavillonVertices[oldIndice];
            pavillonLastLvlVertices[cell+1] = pavillonVertices[oldIndice+1];
            pavillonLastLvlVertices[cell+2] = pavillonVertices[oldIndice+2];

            colorsLastLvlArray[cell]    = color[0];
            colorsLastLvlArray[cell+1]  = color[1];
            colorsLastLvlArray[cell+2]  = color[2];

            pavillonLastLvlIndices[indice] = indice;
            ++indice;
            oldIndice+=3;
            /* second point */
            cell+=3;
            pavillonLastLvlVertices[cell] = pavillonVertices[oldIndice];
            pavillonLastLvlVertices[cell+1] = pavillonVertices[oldIndice+1];
            pavillonLastLvlVertices[cell+2] = pavillonVertices[oldIndice+2];

            colorsLastLvlArray[cell]    = color[0];
            colorsLastLvlArray[cell+1]  = color[1];
            colorsLastLvlArray[cell+2]  = color[2];

            pavillonLastLvlIndices[indice] = indice;
            ++indice;
            oldIndice+=3;

            ++j;
        }
}


Pavillon::~Pavillon()
{
    delete [] pavillonVertices;
    delete [] colorsArray;
    delete [] pavillonIndices;

    delete [] pavillonLastLvlVertices;
    delete [] colorsLastLvlArray;
    delete [] pavillonLastLvlIndices;

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
