#include "TP01.h"

#include "Shapes/Basis.h"
#include "BasicObjects/Cube.h"
#include "Types.h"
#include "diamond.h"
#include "Color.h"

#include <iostream>

#include <QPixmap>
#include "Camera.h"
#include <GlFramework.h>

using namespace std;

/* Camera variables */
GLfloat angle1 = 0;
GLfloat angle2 = 0;

const GLfloat g_AngleSpeed = 1.0f*DEG2RAD;
const GLfloat g_MoveSpeed = 1.0f;

/* Camera variables */
/*Pavillon* g_Pavillon;
Rondiste* g_Rondiste;*/
Diamond* g_diamond;

Camera* g_camera;
bool m_keyRight, m_keyLeft, m_keyDown, m_keyUp; // Translate
bool m_IPlus, m_IMinus, m_KPlus, m_KMinus;      // Rotation
bool m_keySpace;                                // Re-center

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

    g_camera = new Camera();

    m_keyDown = false;
    m_keyLeft = false;
    m_keyRight = false;
    m_keyUp = false;

    cout << endl << "coco1" << endl;
}
TP01::~TP01()
{
    delete g_diamond;
}

bool TP01::initializeObjects()
{
    cout << "coco2" << endl;

    /* Grey background */
	glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
	glEnable( GL_DEPTH_TEST );

    cout << "coco3" << endl;

    /* Shaders settings */
    // createShader("release/Shaders/defaultDiffuseShader");
    createShader("release/Shaders/defaultDiffuseRandomGradientShader");

    cout << "coco4" << endl;

    useShader("defaultDiffuseRandomGradientShader");

    cout << "coco5" << endl;

	return true;
}
void TP01::render()
{
//    // Utilisation de la caméra "classique"
//    // Initialisation de la caméra
//    lookAt(-20, 10, 0, 20, 0, 0);

//    // Rendu des objets
//    pushMatrix();
//        rotate(angle1, 0, 1, 0);
//        rotate(angle2, 1, 0, 0);

//        g_diamond->draw();
//    popMatrix();


    // Utilisation de la caméra libre
    cout << "cocoX" << endl;

    if (m_keySpace) g_camera->reset();

    if (m_keyUp)    g_camera->translateZ(g_MoveSpeed);
    if (m_keyDown)  g_camera->translateZ(-g_MoveSpeed);
    if (m_keyRight) g_camera->translateX(g_MoveSpeed);
    if (m_keyLeft)  g_camera->translateX(-g_MoveSpeed);

    if (m_IPlus)    g_camera->rotateX(g_AngleSpeed);
    if (m_IMinus)   g_camera->rotateX(-g_AngleSpeed);
    if (m_KPlus)    g_camera->rotateY(g_AngleSpeed);
    if (m_KMinus)   g_camera->rotateY(-g_AngleSpeed);

    g_camera->buildViewMatrix();
    g_camera->buildProjectionMatrix();

    g_camera->getViewMatrix().print();

    GLMatrix matView = g_camera->getViewGLMatrix();
    GLMatrix matProj = g_camera->getProjectionGLMatrix();

    setViewMatrix(matView);
    setProjMatrix(matProj);

    g_diamond->draw();

    m_keyUp = false;
    m_keyDown = false;
    m_keyRight = false;
    m_keyLeft = false;
    m_IMinus = false;
    m_IPlus = false;
    m_KPlus = false;
    m_KMinus = false;
    m_keySpace = false;
}

void TP01::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
	{
		case Qt::Key_Escape:
			close();
			break;

        case Qt::Key_Space:
            m_keySpace = true;
            break;

        case Qt::Key_Left:
            m_keyLeft = true;
            break;

        case Qt::Key_Right:
            m_keyRight = true;
            break;

        case Qt::Key_Up:
            m_keyUp = true;
            break;

        case Qt::Key_Down:
            m_keyDown = true;
            break;

        case Qt::Key_Z:
            m_IPlus = true;
            break;

        case Qt::Key_S:
            m_IMinus = true;
            break;

        case Qt::Key_D:
            m_KPlus = true;
            break;

        case Qt::Key_Q:
            m_KMinus = true;
            break;

		case Qt::Key_R:
			angle1 = angle2 = 0.0f;
			break;
	}
}
