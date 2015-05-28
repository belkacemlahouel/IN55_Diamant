#include "crown.h"

Crown::Crown()
{

}


Crown::Crown(float32 radius, float32 table, float32 crownHeight, float32 rondisteHeight,float32 pavillonHeight, float32 lvlCrownHeight, int32 complexity, const GLfloat color[])
{
    /* VBO has not been initialized already */
    this->hasInitiatedVBO = false;

    //nb of points at the second level in the crown.
    int32 nbPtLvl = complexity/2;

    int32 size = nbPtLvl*6;
    int32 iterations, i, start, cell, indice, tmpAngle;
    int32 height = pavillonHeight+rondisteHeight+crownHeight;
    GLfloat* verticeSaver = new GLfloat[nbPtLvl*3];

    verticesPrincipalFacesUpArray = new GLfloat[size];
    verticesLittleFacesUpArray = new GLfloat[size+nbPtLvl*3];

    colorsPrincipalArray = new GLfloat[size];
    colorsLittleFacesArray = new GLfloat[size+nbPtLvl*3];

    verticesPrincipalArraySize = size;
    verticesLittleFacesArraySize = nbPtLvl*9;

    /* Create points for the little triangles, the upper triangles of the quadrilaterals and the color array*/
    float32 angle = 2*M_PI/nbPtLvl;
    float32 principalAngle, trianglesAngle;


    for(i=0; i<nbPtLvl; ++i)
    {
        cell = i*3;
        start = start+i*3;

        principalAngle = (i+0.5)*angle;
        //trianglesAngle = quadAngle - 0.5*angle;
        trianglesAngle = i*(2*M_PI/nbPtLvl);

        //position on x-axis of the new point
        verticesPrincipalFacesUpArray[cell] = table * cos(principalAngle);
        verticesLittleFacesUpArray[cell] = table * cos(trianglesAngle);
        verticeSaver[cell] = verticesPrincipalFacesUpArray[cell];
        //cout << verticesPrincipalFacesUpArray[cell] << " / ";

        //position on y-axis of the new point
        verticesPrincipalFacesUpArray[cell+1] = height;
        verticesLittleFacesUpArray[cell+1] = height;
        verticeSaver[cell+1] = height;
        //cout << verticesPrincipalFacesUpArray[cell+1] << " / ";

        //position on z-axis of the new point
        verticesPrincipalFacesUpArray[cell+2] = table * sin(principalAngle);
        verticesLittleFacesUpArray[cell+2] = table * sin(trianglesAngle);
        verticeSaver[cell+2] = verticesPrincipalFacesUpArray[cell+2];
        //cout << verticesPrincipalFacesUpArray[cell+2]<<endl;

        colorsPrincipalArray[cell]    = color[0];
        colorsPrincipalArray[cell+1]  = color[1];
        colorsPrincipalArray[cell+2]  = color[2];
    }

    /* Creates the points of the first level*/
    iterations = nbPtLvl*2;
    float32 halfRadius = radius*0.5f;
    height = pavillonHeight+rondisteHeight+lvlCrownHeight;

    for(int32 k=nbPtLvl; k<iterations; ++k)
    {
        cell = k*3;
        tmpAngle = (k-1)*angle;

        //position on x-axis of the new point
        verticesPrincipalFacesUpArray[cell] = halfRadius * cos(tmpAngle);
        verticesLittleFacesUpArray[cell] = halfRadius * cos(tmpAngle);

        //position on y-axis of the new point
        verticesPrincipalFacesUpArray[cell+1] = height;
        verticesLittleFacesUpArray[cell+1] = height;

        //position on z-axis of the new point
        verticesPrincipalFacesUpArray[cell+2] = halfRadius * sin(tmpAngle);
        verticesLittleFacesUpArray[cell+2] = halfRadius * sin(tmpAngle);

        colorsPrincipalArray[cell] = color[0];
        colorsPrincipalArray[cell+1] = color[1];
        colorsPrincipalArray[cell+2] = color[2];
    }

    /* Put vertices of the principal faces in the table of vertice of the triangles. */
    int32 num=0;
    for(int32 k=nbPtLvl*6; k<nbPtLvl*9; ++k)
    {
        verticesLittleFacesUpArray[k]=verticeSaver[num];
        ++num;
    }

    /* Create the tables of indices */
    size = nbPtLvl*3;
    indicesLittleFacesArray = new GLushort[(size+3)*2];
    indicesPrincipalArray = new GLushort[size];
    indicesPrincipalArraySize = size;
    indicesLittleFacesArraySize = (size+3)*2;

    /* Create indices for the little triangles */
    for (i=0; i<nbPtLvl; ++i)
    {
        cell = i*3;
        indicesLittleFacesArray[cell]=i;
        indicesLittleFacesArray[cell+1]=nbPtLvl+i;
        indicesLittleFacesArray[cell+2]=nbPtLvl*2+i;
    }

    for (i=0; i<nbPtLvl; ++i)
    {
        cell = nbPtLvl*3 + i*3;
        indicesLittleFacesArray[cell]=i;
        indicesLittleFacesArray[cell+1]=nbPtLvl+i;
        if(i!=0)
        {
            indicesLittleFacesArray[cell+2]=nbPtLvl*2+(i-1);
        }
        else
        {
            indicesLittleFacesArray[cell+2]=nbPtLvl*2+(nbPtLvl-1);
        }
    }

    /* Build the table of indices fo the upper triangles of the quadrilaterals */

    for(i=0;i<nbPtLvl;++i)
    {
        cell=i*3;
        indicesPrincipalArray[cell]=i;

        indice = nbPtLvl+i;
        indicesPrincipalArray[cell+1]=indice;

        /* If indice+1 is superior to nbPtLvl1*2, it means that we gonna go out from the vertices table,
         * we must continue at its beginning */
        if((indice+1) >= (nbPtLvl*2))
        {
            indicesPrincipalArray[cell+2]=nbPtLvl;
        }
        else
        {
            indicesPrincipalArray[cell+2]=indice+1;
        }
    }
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
    glDrawElements(GL_TRIANGLE_FAN, indicesPrincipalArraySize, GL_UNSIGNED_SHORT, 0);

    /* Disable attributes arrays */
    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(colorLocation);
}
