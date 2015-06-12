#ifndef TP01_h
#define TP01_h


#include "GlWindow.h"
#include "Types.h"

#include "lightsource.h"
#include "material.h"


class TP01 : public GlWindow
{
    private:
        int16 shaderID;
        boolean wireframeMode;

        const GLfloat *color;
        LightSource *light;
        Material *material;

        void createLight();
        void createMaterial();

	public:
        TP01(int16 shaderID, boolean wireframeMode);
        ~TP01();

		/*!
		*\brief Initialization des objets.
		*/
		bool initializeObjects();

		/*!
		*\brief Rendu de la scène.
		*/
		void render();

		void keyPressEvent(QKeyEvent *);
};


#endif
