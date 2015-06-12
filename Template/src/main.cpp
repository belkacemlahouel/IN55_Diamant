//*****************************************************************************
//
// Main Program
// Author: Fabrice LAURI (fabrice.lauri@utbm.fr)
//          (Associate Professor at the
//          "Université de Technologie de Belfort-Montbéliard", France)
// Version: 1.0
// Last update: 2012-05-01
//
//*****************************************************************************

#include "TP01.h"

#include <iostream>
#include <limits>
#include <QApplication>
#include <QDesktopWidget>
#include "Types.h"

using namespace std;

int main(int argc, char *argv[])
{
    /* Attributes */
    int16 shaderID = 0;
    int16 wireframeAwnser = 0;
    boolean wireframeMode = false;

    /* Choose of the shader */
    cout << "Hello, " << endl << "we are going to ask you about some parameters." << endl << endl;

    cout << "Which shader do you want :" << endl;
    cout << "\t0. Flat Diffuse " << endl;
    cout << "\t1. Multicolor Diffuse" << endl;
    cout << "\t2. Lighten Flat Diffuse" << endl << endl;

    cout << "Your choice : ";
    cin >> shaderID;
    while(cin.fail() || shaderID < 0 || shaderID > 2){
        cout << "Warning : Invalid input!" << endl << endl;
        cin.clear();

        cout << "Your choice : ";
        cin >> shaderID;
    }

    cout << endl;

    /* Choose of the drawing mode */
    cout << "Choose the drawing mode :" << endl;
    cout << "\t0. Normal Mode " << endl;
    cout << "\t1. Wireframe Mode" << endl << endl;

    cout << "Your choice : ";
    cin >> wireframeAwnser;
    while(cin.fail() || wireframeAwnser < 0 || wireframeAwnser > 1){
        cout << "Warning : Invalid input!" << endl << endl;
        cin.clear();

        cout << "Your choice : ";
        cin >> wireframeAwnser;
    }

    if(wireframeAwnser == 1)
        wireframeMode = true;

    cout << endl;

    /* Create application */
	QApplication app(argc, argv);
    TP01 win(shaderID, wireframeMode);

    win.adjustSize();
    win.move(QApplication::desktop()->screen()->rect().center() - win.rect().center());
	win.show();

	return app.exec();
}

void clearCinBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
