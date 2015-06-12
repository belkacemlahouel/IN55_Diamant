#include "TP01.h"

#include "Shapes/Basis.h"
#include "BasicObjects/Cube.h"
#include "diamond.h"
#include "Color.h"

#include <iostream>

using namespace std;

/* Camera variables */
GLfloat angle1 = 0;
GLfloat angle2 = 0;

const GLfloat g_AngleSpeed = 15.0f;

/* Camera variables */
Diamond* g_diamond;


TP01::TP01(int16 shaderID = 0, boolean wireframeMode = false)
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

    this->shaderID = shaderID;
    this->wireframeMode = wireframeMode;

    this->color = COLOR_SPRINGGREEN;
    g_diamond = new Diamond(pavillon, crown, rondiste, table, radius, complexity, this->color, alpha, lvlPavillon, lvlCrown);
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
    if(this->shaderID == 1){
        createShader("release/Shaders/defaultDiffuseRandomGradientShader");
        useShader("defaultDiffuseRandomGradientShader");
    }
    else if(this->shaderID == 2){
        createShader("release/Shaders/defaultDiffuseLightningShader");
        useShader("defaultDiffuseLightningShader");

        createMaterial();
        createLight();
    }
    else {
        createShader("release/Shaders/defaultDiffuseShader");
        useShader("defaultDiffuseShader");
    }

    if(this->wireframeMode)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	return true;
}
void TP01::render()
{
    /* Initialisation de la caméra */
    lookAt(-20, 10, 0, 20, 0, 0);

    if(this->shaderID == 2)
        this->light->updateLight();

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


void TP01::createMaterial()
{
    GLfloat ambient[] = {0.0215, 0.1745, 0.0215, 1.0};
    GLfloat diffuse[] = {0.07568, 0.61424, 0.07568, 1.0};
    GLfloat specular[] = {0.633, 0.727811, 0.633, 1.0};
    GLfloat shininess = 0.6;

    this->material = new Material(this, ambient, diffuse, specular, shininess);
}
void TP01::createLight()
{
    GLuint id = 0;

    GLfloat posDir[4] = {30.0, 30.0, 30.0, 0.0};

    GLfloat ambient[4] = {0.0, 1.0, 1.0, 1.0};
    GLfloat diffuse[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat specular[4] = {1.0, 1.0, 1.0, 1.0};

    GLfloat constantAttenuation = 2.0;
    GLfloat linearAttenuation = 1.0;
    GLfloat quadraticAttenuation = 0.5;

    GLfloat spotDirection[3] = {0.0, 0.0, 0.0};
    GLfloat spotCutoff = 180;
    GLfloat spotExponent = 0;

    this->light = new LightSource(this, id, posDir, ambient, diffuse, specular,
                                  constantAttenuation, linearAttenuation, quadraticAttenuation,
                                  spotDirection, spotCutoff, spotExponent);
}
