//////////////////////////////////////////////////////////////////////////////////////////
// includes 
//////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
//////////////////////////////////////////////////////////////////////////////////////////
// externals 
//////////////////////////////////////////////////////////////////////////////////////////
extern cRenderClass graphics;

//////////////////////////////////////////////////////////////////////////////////////////
// renderScene() - render the scene
//////////////////////////////////////////////////////////////////////////////////////////

void keyboard(unsigned char key, int x, int y) {
	//Escape = exit
	if (key == 27) {
		exit(0);
	}
	//If the key is spacebar, pause
	if (key == 32) {
		system("pause");
	}
};

void renderScene()
{
	cEmitter emitter;

	if (emitter.isAlive())
	{
		emitter.explode();
	}
	Sleep(1000);
}

//////////////////////////////////////////////////////////////////////////////////////////
// update() - update function
//////////////////////////////////////////////////////////////////////////////////////////
void update()
{
	//Sort of works..
	glutKeyboardFunc(keyboard);

	// always re-render the scene..
	renderScene();
}

//////////////////////////////////////////////////////////////////////////////////////////
// _tmain() - program entry point
//////////////////////////////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{	
	graphics.create(argc, argv);

	graphics.loop();

	return 0;
}