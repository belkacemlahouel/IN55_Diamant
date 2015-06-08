#include "TP01.h"

#include "Shapes/Basis.h"
#include "BasicObjects/Cube.h"
#include "Types.h"
#include "diamond.h"
#include "Color.h"

#include <iostream>

using namespace std;

/* Camera variables */
GLfloat angle1 = 0;
GLfloat angle2 = 0;

const GLfloat g_AngleSpeed = 15.0f;

/* Camera variables */
/*Pavillon* g_Pavillon;
Rondiste* g_Rondiste;*/
Diamond* g_diamond;


TP01::TP01()
{
    setWindowTitle(trUtf8("IN55-DiamondProject"));
    float32 pavillon = 5.0;
    float32 crown = 2.0;
    float32 rondiste = 1.0;
    float32 table = 2.0;
    float32 radius = 5.0;
    //Complexity is the number of triangles in the rondiste.
    int32 complexity = 16;
    float32 alpha = 1.0;
    //Height of the first level of point in the different part of the diamond.
    float32 lvlPavillon = 2.5;
    float32 lvlCrown = 1.0;

    g_diamond = new Diamond(pavillon, crown, rondiste, table, radius, complexity, COLOR_SPRINGGREEN, alpha, lvlPavillon, lvlCrown);
}
TP01::~TP01()
{
    delete g_diamond;
}

bool TP01::initializeObjects()
{
    /* Grey background */
	glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
    glEnable(GL_DEPTH_TEST);

    /* Shaders settings */
    createShader("release/Shaders/defaultDiffuseShader");
    createShader("release/Shaders/defaultDiffuseRandomGradientShader");

    useShader("defaultDiffuseRandomGradientShader");

	return true;
}
void TP01::render()
{
    /* Initialisation de la caméra */
    lookAt(-20, 10, 0, 20, 0, 0);

    /* Rendu des objets */
	pushMatrix();
        rotate(angle1, 0, 1, 0);
        rotate(angle2, 1, 0, 0);

        g_diamond->draw();
	popMatrix();
}

void TP01::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
	{
		case Qt::Key_Escape:
			close();
			break;

		case Qt::Key_Left:
			angle1 -= g_AngleSpeed;
			break;

		case Qt::Key_Right:
			angle1 += g_AngleSpeed;
			break;

		case Qt::Key_Up:
			angle2 -= g_AngleSpeed;
			break;

		case Qt::Key_Down:
			angle2 += g_AngleSpeed;
			break;

		case Qt::Key_R:
			angle1 = angle2 = 0.0f;
			break;
	}
}
