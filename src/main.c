#include "glut.h"
#include "iGraphics.h"


#define FPS 60
/*
	Please try to avoid using the following 2 macros whenever you can.
	Usage of iWidth() and iHeight() is advised. Though there can be cases where you need these macros
*/
#define WIDTH 500
#define HEIGHT 400

void update(void);

void iDraw(void) {
	iClear();
	/*
		This function runs forever. Do NOT update variables inside iDraw. Use iDraw to DRAW stuff only
	*/
}

void update(void) {
	/*
		This function is called once a while (basically after (1 / FPS) seconds). Use it to update your varibales
	*/
}

void iMouseMove(int state) {}

void iMouse(int button, int state, int mx, int my) {}

void iKeyboard(unsigned char key) {}

void iSpecialKeyboard(unsigned char key) {}

int main(void) {
	/*
		Initialize global variables here
	*/

	iSetTimer(1000 / FPS, update);
	iInitialize(WIDTH, HEIGHT, "DEMO");

	/*
		Cleanup here if needed
	*/

	return 0;
}
