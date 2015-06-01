#include "table.h"

Table::Table()
{

}


Table::Table(float32 radiusTable, float32 heightCrown, float32 heightPavillon)
{
    /* VBO has not been initialized already */
    this->hasInitiatedVBO = false;
}


Table::~Table()
{
    delete [] vertices;
    delete [] indices;
    delete [] colors;
}


void Table::initVBO()
{

}


void Table::drawShape(const char *shader_name)
{

}
