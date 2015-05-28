#include "TP01.h"

#include "Shapes/Basis.h"
#include "BasicObjects/Cube.h"
#include "BasicObjects/Pavillon.h"
#include "BasicObjects/rondiste.h"
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
    setWindowTitle(trUtf8("IN55-TP01"));
    /*g_Pavillon = new Pavillon(10.0, 10.0, 5.0, 12, 2.0, COLOR_SPRINGGREEN);
    g_Rondiste = new Rondiste(10.0, 10.0,2.0, 12, COLOR_SPRINGGREEN);*/
    g_diamond = new Diamond();
}
TP01::~TP01()
{
    /*delete g_Pavillon;
    delete g_Rondiste;*/
    delete g_diamond;
}

bool TP01::initializeObjects()
{
    /* Grey background */
	glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
	glEnable( GL_DEPTH_TEST );

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

        /*g_Pavillon->draw();
        g_Rondiste->draw();*/
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
