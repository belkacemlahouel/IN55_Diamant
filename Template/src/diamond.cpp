#include "diamond.h"


Diamond::Diamond()
{
    pavillon = new Pavillon(10.0, 10.0, 5.0, 12, 2.0, COLOR_SPRINGGREEN);
    rondiste = new Rondiste(10.0, 10.0,2.0, 12, COLOR_SPRINGGREEN);
}

Diamond::Diamond(float32 pavillon, float32 crown, float32 rondiste, float32 table, float32 radius, int32 complexity, const GLfloat color[3], float32 alpha, float32 lvlPavillon, float32 lvlCrown)
{
    //complexity must be a multiple of 2
    if(fmod(complexity,2) != 0)
    {
        ++complexity;
    }

    this->pavillon = new Pavillon(radius, pavillon, lvlPavillon, complexity, rondiste, color);
    this->rondiste = new Rondiste(radius, pavillon, rondiste, complexity, color);
    this->crown = new Crown(radius, table, crown, rondiste, pavillon, lvlCrown, complexity, color);
    this->table = new Table(table, crown, pavillon, complexity, color);
}
Diamond::~Diamond()
{
    delete this->pavillon;
    delete this->rondiste;
    delete this->crown;
    delete this->table;
}

/**
 * @brief Diamond::draw
 * Draw the different parts of the diamond.
 * @param shader_name
 */
void Diamond::drawShape(const char *shader_name)
{
    pavillon->draw();
    rondiste->draw();
    crown->draw();
    table->draw();
}
