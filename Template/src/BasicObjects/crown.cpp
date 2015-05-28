#include "crown.h"

Crown::Crown()
{

}


Crown::Crown(float32 radius, float32 crownHeight, float32 rondisteHeight, float32 lvlCrownHeight, int32 complexity, const GLfloat color[])
{

}


Crown::~Crown()
{
    delete [] verticesArray;
    delete [] colorsArray;
    delete [] indicesArray;

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

}


/**
 * @brief Crown::drawShape
 * Draw the crown of a diamond
 * @param shader_name
 */
void Crown::drawShape(const char *shader_name){

}
