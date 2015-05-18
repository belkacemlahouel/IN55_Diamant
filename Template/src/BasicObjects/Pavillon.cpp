#include "Pavillon.h"


Pavillon::Pavillon()
{

}

Pavillon::Pavillon(float radius, float heigth, float heigthFirstLvl, float complexity)
{
    //nb of points at the second level in pavillon.
    int nbPtLvl1 = complexity/2;

    //to begin I just construct the peak and the first level
    int size = 3*(nbPtLvl1+1);
    GLfloat vertices[size];

    //peak
    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    vertices[2] = 0.0f;

    /** TODO
      * each point i on the lvl 1 will have its coordinates equal to
      * x = radius * cos(i*(2*pi/nbPtLvl1))
      * y = radius * sin(i*(2*pi/nbPtLvl1))
      * z = heigthFirstLvl
      * */
}
