#include "crown.h"

Crown::Crown()
{

}


Crown::Crown(float32 radius, float32 table, float32 crownHeight, float32 rondisteHeight,float32 pavillonHeight, float32 lvlCrownHeight, int32 complexity, const GLfloat color[])
{
    /* VBO has not been initialized already */
    this->hasInitiatedVBO = false;

    /* Used to rotate the upper triangles around y-axis. */
    Matrix* rotationY = new Matrix();
    int32 cell, i;
    int32 nbFaces = complexity/4;
    int32 nbPoint = nbFaces * 3;
    int32 size = nbPoint*3;
    int32 iterations = size/9;
    float32 angle = 2*M_PI/(nbFaces*2);
    float32 anglePhase1, anglePhase2;
    float32 height = pavillonHeight+lvlCrownHeight;

    verticesPrincipalFacesUpArray = new GLfloat[size];
    verticesPrincipalArraySize = size;
    verticesLittleFacesUpArray = new GLfloat[size];
    //verticesLittleFacesArraySize = size;
    colorsPrincipalArray = new GLfloat[size];
    colorsPrincipalArraySize = size;

    /* Creation of the big quadrilaterals and the array of color */
    for(i=0; i<iterations; ++i)
    {
        cell = i*9;

        anglePhase2 = (i-0.25)*angle*2;
        anglePhase1 = (i+0.25)*angle*2;

        //position of the first point
        verticesPrincipalFacesUpArray[cell] = radius * cos(anglePhase2);
        verticesPrincipalFacesUpArray[cell+1] = height;
        verticesPrincipalFacesUpArray[cell+2] = radius * sin(anglePhase2);

        //position of the second point
        verticesPrincipalFacesUpArray[cell+3] = radius * cos(anglePhase1);
        verticesPrincipalFacesUpArray[cell+4] = pavillonHeight;
        verticesPrincipalFacesUpArray[cell+5] = radius * sin(anglePhase1);

        //position of the third point
        verticesPrincipalFacesUpArray[cell+6] = table * cos(anglePhase1);
        verticesPrincipalFacesUpArray[cell+7] = pavillonHeight + crownHeight;
        verticesPrincipalFacesUpArray[cell+8] = table * sin(anglePhase1);

        colorsPrincipalArray[cell]    = color[0];
        colorsPrincipalArray[cell+1]  = color[1];
        colorsPrincipalArray[cell+2]  = color[2];

        colorsPrincipalArray[cell+3]  = color[0];
        colorsPrincipalArray[cell+4]  = color[1];
        colorsPrincipalArray[cell+5]  = color[2];

        colorsPrincipalArray[cell+6]  = color[0];
        colorsPrincipalArray[cell+7]  = color[1];
        colorsPrincipalArray[cell+8]  = color[2];
    }

    /* Creation of the upper triangles*/
    for(i=0; i<iterations; ++i)
    {
        cell = i*9;

        /*anglePhase1 = (i+0.25)*angle*2;
        anglePhase2 = (i-0.25)*angle*2;*/
        anglePhase1 = (i-0.25)*angle*2;
        anglePhase2 = (i+0.25)*angle*2;

        //position of the first point
        verticesLittleFacesUpArray[cell] = table * cos(anglePhase1);
        verticesLittleFacesUpArray[cell+1] = pavillonHeight + crownHeight;
        verticesLittleFacesUpArray[cell+2] = table * sin(anglePhase1);

        //position of the second point
        verticesLittleFacesUpArray[cell+3] = radius * cos(anglePhase2);
        verticesLittleFacesUpArray[cell+4] = height;
        verticesLittleFacesUpArray[cell+5] = radius * sin(anglePhase2);

        //position of the third point
        verticesLittleFacesUpArray[cell+6] = table * cos(anglePhase2);
        verticesLittleFacesUpArray[cell+7] = pavillonHeight + crownHeight;
        verticesLittleFacesUpArray[cell+8] = table * sin(anglePhase2);
    }

    /* Initialize the array of indices */
    //Each faces have 2 triangles of 3 points.
    indicesPrincipalArraySize = nbFaces*6;
    indicesPrincipalArray = new GLushort[indicesPrincipalArraySize];

    /* Initialize indices of the big quadrilaterals*/
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

    /* Correction of a wrong indice. */
    indicesPrincipalArray[indicesPrincipalArraySize-1]=0;



    /* Initialize indices of the big quadrilaterals*/
    indicesLittleFacesUpArray = new GLushort[indicesPrincipalArraySize];
    i = 0;
    cell = 0;
    int32 coef = nbFaces - 2;

    while(cell<indicesPrincipalArraySize)
    {
        //indicesLittleFacesUpArray[cell]=i;
        indicesLittleFacesUpArray[cell]=i;
        indicesLittleFacesUpArray[cell+1]=i+1;
        indicesLittleFacesUpArray[cell+2]=i+2;
        indicesLittleFacesUpArray[cell+3]=i+1;
        indicesLittleFacesUpArray[cell+4]=i+2;

        if(i+3 < nbPoint){
            indicesLittleFacesUpArray[cell+5]=i+3;
        }else{
            indicesLittleFacesUpArray[cell+5]=0;
        }

        cell+=6;
        i+=3;
    }

    /* Rotation of the vertices of upper triangles around y-axis. */
    GLfloat* point = new GLfloat[4];
    rotationY->createRotationMatrixY(angle);

    //rotationY->printMatrix();
    i=0;


    while(i<verticesPrincipalArraySize)
    {
        /*initialization of the point's coordinates. */
        point[0]=verticesLittleFacesUpArray[i];
        point[1]=verticesLittleFacesUpArray[i+1];
        point[2]=verticesLittleFacesUpArray[i+2];
        point[3]=1;

        point = rotationY->productMatVec(point);

        verticesLittleFacesUpArray[i] = point[0];
        verticesLittleFacesUpArray[i+1] = point[1];
        verticesLittleFacesUpArray[i+2] = point[2];

        i+=3;
    }

    /* Create the little triangles down crown. */
    createDownTriangles(radius, table, crownHeight, rondisteHeight, pavillonHeight, lvlCrownHeight, complexity, color);

    normalsPrincipalFacesUpArray = new GLfloat[verticesPrincipalArraySize];
    computeNormals(normalsPrincipalFacesUpArray, verticesPrincipalFacesUpArray, verticesPrincipalArraySize, indicesPrincipalArray, indicesPrincipalArraySize);

    normalsLittleFacesUpArray = new GLfloat[verticesPrincipalArraySize];
    computeNormals(normalsLittleFacesUpArray, verticesLittleFacesUpArray, verticesPrincipalArraySize, indicesLittleFacesUpArray, indicesPrincipalArraySize);

    normalsTrianglesDownArray = new GLfloat[verticesTrianglesDownArraySize];
    computeNormals(normalsTrianglesDownArray, verticesTrianglesDownArray, verticesTrianglesDownArraySize, indicesLittleFacesDownArray, indicesLittleFacesDownArraySize);
}

/**
 * @brief Crown::createDownTriangles
 * Create the little triangles down crown.
 * @param radius
 * @param table
 * @param crownHeight
 * @param rondisteHeight
 * @param pavillonHeight
 * @param lvlCrownHeight
 * @param complexity
 * @param color
 */
void Crown::createDownTriangles(float32 radius, float32 table, float32 crownHeight, float32 rondisteHeight, float32 pavillonHeight, float32 lvlCrownHeight, int32 complexity, const GLfloat color[3])
{
    int32 nbFaces = complexity/4;
    int32 nbPoint = nbFaces * 6;
    int32 size = nbPoint*3;
    float32 angleRondiste = 2*M_PI/complexity;
    float32 anglePhase1, anglePhase2;
    float32 halfHeight = rondisteHeight/2;
    int32 i, j, cell;

    verticesTrianglesDownArray = new GLfloat[size];
    verticesTrianglesDownArraySize = size;

    indicesLittleFacesDownArraySize = nbFaces*4*3;
    indicesLittleFacesDownArray = new GLushort[indicesLittleFacesDownArraySize];

    colorsTrianglesDownArray = new GLfloat[size];

    /* Create vertices */
    i=0;
    /* Number of faces created */
    j=0;

    /* We dicrease the i because of the direction of rotation */
    while( j< nbFaces){
        cell = j*18;

        anglePhase2 = (i+0.5)*angleRondiste*2;  //angle of hole in the rondiste
        anglePhase1 = (i)*angleRondiste*2;      //angle of high point of the rondiste
        //position of the first point
        verticesTrianglesDownArray[cell] = radius * cos(anglePhase2);
        verticesTrianglesDownArray[cell+1] = pavillonHeight;
        verticesTrianglesDownArray[cell+2] = radius * sin(anglePhase2);


        //position of the second point
        verticesTrianglesDownArray[cell+3] = radius * cos(anglePhase1);
        verticesTrianglesDownArray[cell+4] = pavillonHeight + halfHeight;
        verticesTrianglesDownArray[cell+5] = radius * sin(anglePhase1);

        --i;
        anglePhase2 = (i+0.5)*angleRondiste*2;  //angle of hole in the rondiste
        anglePhase1 = (i)*angleRondiste*2;  //angle of high point of the rondiste
        //position of the third point
        verticesTrianglesDownArray[cell+6] = radius * cos(anglePhase2);
        verticesTrianglesDownArray[cell+7] = pavillonHeight + lvlCrownHeight;
        verticesTrianglesDownArray[cell+8] = radius * sin(anglePhase2);

        //position of the fourth point
        verticesTrianglesDownArray[cell+9] = radius * cos(anglePhase2);
        verticesTrianglesDownArray[cell+10] = pavillonHeight;
        verticesTrianglesDownArray[cell+11] = radius * sin(anglePhase2);

        //position of the fifth point
        verticesTrianglesDownArray[cell+12] = radius * cos(anglePhase1);
        verticesTrianglesDownArray[cell+13] = pavillonHeight + halfHeight;
        verticesTrianglesDownArray[cell+14] = radius * sin(anglePhase1);

        --i;
        anglePhase2 = (i+0.5)*angleRondiste*2;  //angle of hole in the rondiste
        //position of the sixth point
        verticesTrianglesDownArray[cell+15] = radius * cos(anglePhase2);
        verticesTrianglesDownArray[cell+16] = pavillonHeight;
        verticesTrianglesDownArray[cell+17] = radius * sin(anglePhase2);

        ++j;
    }

    /* Initialize colors array */
    for(i=0; i<nbPoint; ++i)
    {
        cell = i*3;

        colorsTrianglesDownArray[cell]    = color[0];
        colorsTrianglesDownArray[cell+1]  = color[1];
        colorsTrianglesDownArray[cell+2]  = color[2];
    }

    /* Initialize indices array */
    i=0;
    cell=0;

    while(cell<indicesLittleFacesDownArraySize)
    {
        indicesLittleFacesDownArray[cell] = i;
        indicesLittleFacesDownArray[cell+1] = i+1;
        indicesLittleFacesDownArray[cell+2] = i+2;
        indicesLittleFacesDownArray[cell+3] = i+1;
        indicesLittleFacesDownArray[cell+4] = i+2;
        indicesLittleFacesDownArray[cell+5] = i+3;
        indicesLittleFacesDownArray[cell+6] = i+2;
        indicesLittleFacesDownArray[cell+7] = i+3;
        indicesLittleFacesDownArray[cell+8] = i+4;
        indicesLittleFacesDownArray[cell+9] = i+2;
        indicesLittleFacesDownArray[cell+10] = i+4;
        indicesLittleFacesDownArray[cell+11] = i+5;

        cell+=12;
        i+=6;
    }
    indicesLittleFacesDownArray[cell-1] = 0;
}

Crown::~Crown()
{
    delete [] verticesPrincipalFacesUpArray;
    delete [] verticesLittleFacesUpArray;
    delete [] verticesTrianglesDownArray;

    delete [] indicesPrincipalArray;
    delete [] indicesLittleFacesUpArray;
    delete [] indicesLittleFacesDownArray;

    delete [] colorsPrincipalArray;
    delete [] colorsTrianglesDownArray;

    delete [] normalsPrincipalFacesUpArray;
    delete [] normalsLittleFacesUpArray;
    delete [] normalsTrianglesDownArray;

    glDeleteBuffers(1, &VertexPrincipalFacesVBOID);
    glDeleteBuffers(1, &ColorPrincipalFacesVBOID);
    glDeleteBuffers(1, &IndicesPrincipalFacesVBOID);
    glDeleteBuffers(1, &NormalsPrincipalFacesVBOID);

    glDeleteBuffers(1, &VertexUpperTrianglesVBOID);
    glDeleteBuffers(1, &ColorUpperTrianglesVBOID);
    glDeleteBuffers(1, &IndicesUpperTrianglesVBOID);
    glDeleteBuffers(1, &NormalsUpperTrianglesVBOID);

    glDeleteBuffers(1, &VertexDownTrianglesVBOID);
    glDeleteBuffers(1, &ColorDownTrianglesVBOID);
    glDeleteBuffers(1, &IndicesDownTrianglesVBOID);
    glDeleteBuffers(1, &NormalsDownTrianglesVBOID);
}


/**
 * @brief Crown::initVBO
 * Initialize the vertex buffer
 */
void Crown::initVBO()
{
    /* VBOs generation & binding for the principal faces (big quadrilaterals)*/
    glGenBuffers(1, &VertexPrincipalFacesVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, VertexPrincipalFacesVBOID);
    glBufferData(GL_ARRAY_BUFFER, verticesPrincipalArraySize*sizeof(GLfloat), verticesPrincipalFacesUpArray, GL_STATIC_DRAW);

    glGenBuffers(1, &ColorPrincipalFacesVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, ColorPrincipalFacesVBOID);
    glBufferData(GL_ARRAY_BUFFER, colorsPrincipalArraySize*sizeof(GLfloat), colorsPrincipalArray, GL_STATIC_DRAW);

    glGenBuffers(1, &IndicesPrincipalFacesVBOID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesPrincipalFacesVBOID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesPrincipalArraySize*sizeof(GLushort), indicesPrincipalArray, GL_STATIC_DRAW);

    glGenBuffers(1, &NormalsPrincipalFacesVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, NormalsPrincipalFacesVBOID);
    glBufferData(GL_ARRAY_BUFFER, verticesPrincipalArraySize*sizeof(GLfloat), normalsPrincipalFacesUpArray, GL_STATIC_DRAW);

    /* VBOs generation & binding for the upper triangles*/
    glGenBuffers(1, &VertexUpperTrianglesVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, VertexUpperTrianglesVBOID);
    glBufferData(GL_ARRAY_BUFFER, verticesPrincipalArraySize*sizeof(GLfloat), verticesLittleFacesUpArray, GL_STATIC_DRAW);

    glGenBuffers(1, &ColorUpperTrianglesVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, ColorUpperTrianglesVBOID);
    glBufferData(GL_ARRAY_BUFFER, colorsPrincipalArraySize*sizeof(GLfloat), colorsPrincipalArray, GL_STATIC_DRAW);

    glGenBuffers(1, &IndicesUpperTrianglesVBOID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesUpperTrianglesVBOID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesPrincipalArraySize*sizeof(GLushort), indicesLittleFacesUpArray, GL_STATIC_DRAW);

    glGenBuffers(1, &NormalsUpperTrianglesVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, NormalsUpperTrianglesVBOID);
    glBufferData(GL_ARRAY_BUFFER, verticesPrincipalArraySize*sizeof(GLfloat), normalsLittleFacesUpArray, GL_STATIC_DRAW);

    /* VBOs generation & binding for the down triangles*/
    glGenBuffers(1, &VertexDownTrianglesVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, VertexDownTrianglesVBOID);
    glBufferData(GL_ARRAY_BUFFER, verticesTrianglesDownArraySize*sizeof(GLfloat), verticesTrianglesDownArray, GL_STATIC_DRAW);

    glGenBuffers(1, &ColorDownTrianglesVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, ColorDownTrianglesVBOID);
    glBufferData(GL_ARRAY_BUFFER, verticesTrianglesDownArraySize*sizeof(GLfloat), colorsTrianglesDownArray, GL_STATIC_DRAW);

    glGenBuffers(1, &IndicesDownTrianglesVBOID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesDownTrianglesVBOID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLittleFacesDownArraySize*sizeof(GLushort), indicesLittleFacesDownArray, GL_STATIC_DRAW);

    glGenBuffers(1, &NormalsDownTrianglesVBOID);
    glBindBuffer(GL_ARRAY_BUFFER, NormalsDownTrianglesVBOID);
    glBufferData(GL_ARRAY_BUFFER, verticesTrianglesDownArraySize*sizeof(GLfloat), normalsTrianglesDownArray, GL_STATIC_DRAW);

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
    GLint normalLocation = glGetAttribLocation(m_Framework->getCurrentShaderId(), "normal");

    glEnableVertexAttribArray(positionLocation);
    glEnableVertexAttribArray(colorLocation);
    glEnableVertexAttribArray(normalLocation);

    /* Initiate the VBO if it has not been done already */
    if(!hasInitiatedVBO)
        this->initVBO();

    /* Draw the principal faces of the crown */
    glBindBuffer(GL_ARRAY_BUFFER, VertexPrincipalFacesVBOID);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, ColorPrincipalFacesVBOID);
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, NormalsPrincipalFacesVBOID);
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesPrincipalFacesVBOID);
    glDrawElements(GL_TRIANGLES, indicesPrincipalArraySize, GL_UNSIGNED_SHORT, 0);

    /* Draw the upper triangles of the crown */
    glBindBuffer(GL_ARRAY_BUFFER, VertexUpperTrianglesVBOID);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, ColorUpperTrianglesVBOID);
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, NormalsUpperTrianglesVBOID);
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesUpperTrianglesVBOID);
    glDrawElements(GL_TRIANGLES, indicesPrincipalArraySize, GL_UNSIGNED_SHORT, 0);

    /* Draw the down triangles of the crown */
    glBindBuffer(GL_ARRAY_BUFFER, VertexDownTrianglesVBOID);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, ColorDownTrianglesVBOID);
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, NormalsDownTrianglesVBOID);
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndicesDownTrianglesVBOID);
    glDrawElements(GL_TRIANGLES, indicesLittleFacesDownArraySize, GL_UNSIGNED_SHORT, 0);

    /* Disable attributes arrays */
    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(colorLocation);
    glDisableVertexAttribArray(normalLocation);
}
