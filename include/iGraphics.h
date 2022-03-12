/*
  Original Author: S. M. Shahriar Nirjon
*/

#define IMOUSE_DRAGGED 0
#define IMOUSE_MOVED 1

void iDraw(void);
void iKeyboard(unsigned char);
void iSpecialKeyboard(unsigned char);
void iMouseMove(int state);
void iMouse(int button, int state, int x, int y);

int iWidth(void);
int iHeight(void);
int iMouseX(void);
int iMouseY(void);
int iSetTimer(int msec, void (*f)(void));
void iPauseTimer(int index);
void iResumeTimer(int index);
void iShowBMP2(int x, int y, char const *filename, int ignoreColor);
void iShowBMP(int x, int y, char const *filename);
void iGetPixelColor(int x, int y, int rgb[]);
void iText(double x, double y, char const *str, void* font);
void iPoint(double x, double y, int size);
void iLine(double x1, double y1, double x2, double y2);
void iFilledPolygon(double x[], double y[], int n);
void iPolygon(double x[], double y[], int n);
void iRectangle(double left, double bottom, double dx, double dy);
void iFilledRectangle(double left, double bottom, double dx, double dy);
void iFilledCircle(double x, double y, double r, int slices);
void iCircle(double x, double y, double r, int slices);
void iEllipse(double x, double y, double a, double b, int slices);
void iFilledEllipse(double x, double y, double a, double b, int slices);
void iRotate(double x, double y, double degree);
void iUnRotate(void);
void iSetColor(double r, double g, double b);
void iDelay(int sec);
void iClear(void);
void iInitialize(int width, int height, char const *title);
