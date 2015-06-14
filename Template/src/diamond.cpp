#include "diamond.h"


Diamond::Diamond()
{
    pavillon = new Pavillon(10.0, 10.0, 5.0, 12, 2.0, COLOR_SPRINGGREEN);
    rondiste = new Rondiste(10.0, 10.0,2.0, 12, COLOR_SPRINGGREEN);
}

Diamond::Diamond(float32 pavillon, float32 crown, float32 rondiste, float32 table, float32 radius, int32 complexity, const GLfloat color[3], float32 alpha, float32 lvlPavillon, float32 lvlCrown)
{
    this->alpha = alpha;
    this->hasSetAlpha = false;
    
    //complexity must be a multiple of 2 because there 2 triangles per faces in the rondiste
    if(fmod(complexity,2) != 0)
    {
        ++complexity;
    }

    //complexity must be a multiple of 4 for the crown faces.
    while(fmod(complexity,4)!=0)
    {
        ++complexity;
    }

    //Test the level of the crown
    if(lvlCrown>=crown){
        lvlCrown = crown/2;
    }

    //Test the level of the pavillon
    if(lvlPavillon>=pavillon){
        lvlPavillon = pavillon/2;
    }

    /*------------------Test if some parameters are equals to zero ------------------*/

    if(pavillon==0.0)
    {
        pavillon = 5;
    }

    if(crown == 0.0)
    {
        crown = 2.0;
    }

    if(rondiste==0.0)
    {
        rondiste = 1.0;
    }

    if(table==0.0)
    {
        table = 2.0;
    }

    if(radius==0.0)
    {
        radius = 5.0;
    }

    if(complexity==0)
    {
        complexity = 16;
    }

    if(lvlPavillon==0.0){
        lvlPavillon = 2.5;
    }

    if(lvlCrown==0.0){
        lvlCrown = 1.0;
    }


    this->pavillon = new Pavillon(radius, pavillon, lvlPavillon, complexity, rondiste, color);
    /*this->rondiste = new Rondiste(radius, pavillon, rondiste, complexity, color);
    this->crown = new Crown(radius, table, crown, rondiste, pavillon, lvlCrown, complexity, color);
    this->table = new Table(table, crown, pavillon, complexity, color);*/
}
Diamond::~Diamond()
{
    delete this->pavillon;
    /*delete this->rondiste;
    delete this->crown;
    delete this->table;*/
}

/**
 * @brief Diamond::draw
 * Draw the different parts of the diamond.
 * @param shader_name
 */
void Diamond::drawShape(const char *shader_name)
{
    /* Init some shader variables */
    if(!hasSetAlpha && this->setAlpha(this->alpha))
        this->hasSetAlpha = true;

    pavillon->draw();
    /*rondiste->draw();
    crown->draw();
    table->draw();*/
}
