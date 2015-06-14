#include "TP01.h"

#include "Shapes/Basis.h"
#include "BasicObjects/Cube.h"
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

const GLfloat g_AngleSpeed = 2.0f*DEG2RAD;
const GLfloat g_MoveSpeed = 1.0f;

/* Camera variables */
Diamond* g_diamond;

Camera* g_camera;
bool m_keyRight, m_keyLeft, m_keyDown, m_keyUp; // Translate
bool m_IPlus, m_IMinus, m_KPlus, m_KMinus;      // Rotation
bool m_keySpace;                                // Re-center

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

    g_camera = new Camera();

    m_keyDown = false;
    m_keyLeft = false;
    m_keyRight = false;
    m_keyUp = false;
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

    bool find = false;

    /* Shaders settings */
    if(this->shaderID == 1){
        createShader("release/Shaders/defaultDiffuseRandomGradientShader");
        useShader("defaultDiffuseRandomGradientShader");
    }
    else if(this->shaderID == 2){
        createShader("release/Shaders/defaultDiffuseLightningShader");
        find = useShader("defaultDiffuseLightningShader");

        createMaterial();
        createLight();
    }
    else {
        createShader("release/Shaders/defaultDiffuseShader");
        find = useShader("defaultDiffuseShader");
    }

    if(this->wireframeMode == true)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	return true;
}
void TP01::render()
{
    // Utilisation de la caméra libre
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

    GLMatrix matView = g_camera->getViewGLMatrix();
    GLMatrix matProj = g_camera->getProjectionGLMatrix();

    setViewMatrix(matView);
    setProjMatrix(matProj);

    if(this->shaderID == 2)
        this->light->updateLight();
    g_diamond->draw();

    /*pushMatrix();
        translate(0.0f, 7.0f, 1.0f);
        float color[] = {1.0f, 1.0f, 0.0f};
        Cube cu = Cube(7.0f, color);
        cu.draw();
    popMatrix();*/

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
            m_keyDown = true;
            break;

        case Qt::Key_Down:
            m_keyUp = true;
            break;

        case Qt::Key_Z:
            m_IMinus = true;
            break;

        case Qt::Key_S:
            m_IPlus = true;
            break;

        case Qt::Key_D:
            m_KPlus = true;
            break;

        case Qt::Key_Q:
            m_KMinus = true;
            break;

//		case Qt::Key_R:
//			angle1 = angle2 = 0.0f;
//			break;
	}
}


void TP01::createMaterial()
{
    GLfloat ambient[] = {0.0215, 0.1745, 0.0215, 1.0};
    GLfloat diffuse[] = {0.07568, 0.61424, 0.07568, 1.0};
    GLfloat specular[] = {0.633, 0.727811, 0.633, 1.0};
    GLfloat shininess = 128*0.6;

    this->material = new Material(this, ambient, diffuse, specular, shininess);
}
void TP01::createLight()
{
    GLuint id = 0;

    GLfloat posDir[4] = {10, 10, -15, 0.0};

    GLfloat ambient[4] = {0.1, 0.1, 0.1, 1.0};
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
