#include "iGraphics.h"

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "glut.h"
#include <time.h>
#include <math.h>
#include "glaux.h"

int iScreenHeight, iScreenWidth;
int mouseX, mouseY;
int ifft=0;
void (*iAnimFunction[10])(void)={0};
int iAnimCount=0;
int iAnimDelays[10];
int iAnimPause[10];

void resize(int width, int height);
void displayFF(void);
void animFF(void);
void keyboardHandler1FF(unsigned char key, int x, int y);
void keyboardHandler2FF(int key, int x, int y);
void mouseMoveHandlerFF(int mx, int my);
void mouseHandlerFF(int button, int state, int x, int y);
void mousePassiveMoveHandlerFF(int mx, int my);

void __stdcall iA0(HWND h, UINT u, UINT_PTR up, DWORD d);
void __stdcall iA1(HWND h, UINT u, UINT_PTR up, DWORD d);
void __stdcall iA2(HWND h, UINT u, UINT_PTR up, DWORD d);
void __stdcall iA3(HWND h, UINT u, UINT_PTR up, DWORD d);
void __stdcall iA4(HWND h, UINT u, UINT_PTR up, DWORD d);
void __stdcall iA5(HWND h, UINT u, UINT_PTR up, DWORD d);
void __stdcall iA6(HWND h, UINT u, UINT_PTR up, DWORD d);
void __stdcall iA7(HWND h, UINT u, UINT_PTR up, DWORD d);
void __stdcall iA8(HWND h, UINT u, UINT_PTR up, DWORD d);
void __stdcall iA9(HWND h, UINT u, UINT_PTR up, DWORD d);

void __stdcall iA0(HWND h, UINT u, UINT_PTR up, DWORD d){if(!iAnimPause[0])iAnimFunction[0]();}
void __stdcall iA1(HWND h, UINT u, UINT_PTR up, DWORD d){if(!iAnimPause[1])iAnimFunction[1]();}
void __stdcall iA2(HWND h, UINT u, UINT_PTR up, DWORD d){if(!iAnimPause[2])iAnimFunction[2]();}
void __stdcall iA3(HWND h, UINT u, UINT_PTR up, DWORD d){if(!iAnimPause[3])iAnimFunction[3]();}
void __stdcall iA4(HWND h, UINT u, UINT_PTR up, DWORD d){if(!iAnimPause[4])iAnimFunction[4]();}
void __stdcall iA5(HWND h, UINT u, UINT_PTR up, DWORD d){if(!iAnimPause[5])iAnimFunction[5]();}
void __stdcall iA6(HWND h, UINT u, UINT_PTR up, DWORD d){if(!iAnimPause[6])iAnimFunction[6]();}
void __stdcall iA7(HWND h, UINT u, UINT_PTR up, DWORD d){if(!iAnimPause[7])iAnimFunction[7]();}
void __stdcall iA8(HWND h, UINT u, UINT_PTR up, DWORD d){if(!iAnimPause[8])iAnimFunction[8]();}
void __stdcall iA9(HWND h, UINT u, UINT_PTR up, DWORD d){if(!iAnimPause[9])iAnimFunction[9]();}

int iSetTimer(int msec, void (*f)(void)) {
  int i = iAnimCount;

  if(iAnimCount>=10){
    fprintf(stderr, "Error: Maximum number of already timer used.\n");
    return -1;
  }

  iAnimFunction[i] = f;
  iAnimDelays[i] = msec;
  iAnimPause[i] = 0;

  if(iAnimCount == 0) SetTimer(0, 0, (UINT) msec, iA0);
  if(iAnimCount == 1) SetTimer(0, 0, (UINT) msec, iA1);
  if(iAnimCount == 2) SetTimer(0, 0, (UINT) msec, iA2);
  if(iAnimCount == 3) SetTimer(0, 0, (UINT) msec, iA3);
  if(iAnimCount == 4) SetTimer(0, 0, (UINT) msec, iA4);

  if(iAnimCount == 5) SetTimer(0, 0, (UINT) msec, iA5);
  if(iAnimCount == 6) SetTimer(0, 0, (UINT) msec, iA6);
  if(iAnimCount == 7) SetTimer(0, 0, (UINT) msec, iA7);
  if(iAnimCount == 8) SetTimer(0, 0, (UINT) msec, iA8);
  if(iAnimCount == 9) SetTimer(0, 0, (UINT) msec, iA9);
  iAnimCount++;

  return iAnimCount-1;
}

void iPauseTimer(int index) {
  if(index>=0 && index<iAnimCount){
    iAnimPause[index] = 1;
  }
}

void iResumeTimer(int index){
  if(index>=0 && index <iAnimCount){
    iAnimPause[index] = 0;
  }
}


/*
 Puts a BMP image on screen

 parameters:
  x - x coordinate
  y - y coordinate
  filename - name of the BMP file
  ignoreColor - A specified color that should not be rendered. If you have an
        image strip that should be rendered on top of another back
        ground image, then the background of the image strip should
        not get rendered. Use the background color of the image strip
        in ignoreColor parameter. Then the strip's background does
        not get rendered.

        To disable this feature, put -1 in this parameter
*/

void iShowBMP2(int x, int y, char const *filename, int ignoreColor) {
  int i,j,k, width, height, nPixels, *rgPixels;
  AUX_RGBImageRec *TextureImage;
  TextureImage = auxDIBImageLoad(filename);

  width = TextureImage->sizeX;
  height = TextureImage->sizeY;
  nPixels = width * height;
  rgPixels = (int *) calloc((size_t) nPixels, sizeof(int));

  for (i = 0, j=0; i < nPixels; i++, j += 3)
  {
    int rgb = 0;
    for(k = 2; k >= 0; k--)
    {
      rgb = ((rgb << 8) | TextureImage->data[j+k]);
    }

    rgPixels[i] = (rgb == ignoreColor) ? 0 : 255;
    rgPixels[i] = ((rgPixels[i] << 24) | rgb);
  }

  glRasterPos2f((GLfloat) x, (GLfloat) y);
  glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, rgPixels);

  free(rgPixels);
  free(TextureImage->data);
  free(TextureImage);
}

void iShowBMP(int x, int y, char const *filename) {
  iShowBMP2(x, y, filename, -1);
}




void iGetPixelColor (int x, int y, int rgb[]) {
  GLubyte pixel[3];
  glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(void *)pixel);

  rgb[0] = pixel[0];
  rgb[1] = pixel[1];
  rgb[2] = pixel[2];

  /* printf("%d %d %d\n",pixel[0],pixel[1],pixel[2]); */
}

void iText(double x, double y, char const *str, void *font) {
  int i;

  if (!font) {
    font = GLUT_BITMAP_8_BY_13;
  }

  glRasterPos3d(x, y, 0);
  for (i=0; str[i]; i++) {
    glutBitmapCharacter(font, str[i]); /*,GLUT_BITMAP_8_BY_13, GLUT_BITMAP_TIMES_ROMAN_24 */
  }
}


void iPoint(double x, double y, int size) {
  int i, j;

  if (size < 0) {
    size = 0;
  }

  glBegin(GL_POINTS);
  glVertex2f((GLfloat) x, (GLfloat) y);
  for(i=(int)x-size;i<x+size;i++)
  {
    for(j=(int)y-size; j<y+size;j++)
    {
      glVertex2f((GLfloat) i, (GLfloat) j);
    }
  }
  glEnd();
}


void iLine(double x1, double y1, double x2, double y2) {
  glBegin(GL_LINE_STRIP);
  glVertex2f((GLfloat) x1, (GLfloat) y1);
  glVertex2f((GLfloat) x2, (GLfloat) y2);
  glEnd();
}

void iFilledPolygon(double x[], double y[], int n) {
  int i;
  if(n<3)return;
  glBegin(GL_POLYGON);
  for(i = 0; i < n; i++){
    glVertex2f((GLfloat) x[i], (GLfloat) y[i]);
  }
  glEnd();
}

void iPolygon(double x[], double y[], int n) {
  int i;
  if(n<3)return;
  glBegin(GL_LINE_STRIP);
  for(i = 0; i < n; i++){
    glVertex2f((GLfloat) x[i], (GLfloat) y[i]);
  }
  glVertex2f((GLfloat) x[0], (GLfloat) y[0]);
  glEnd();
}

void iRectangle(double left, double bottom, double dx, double dy) {
  double x1, y1, x2, y2;

  x1 = left;
  y1 = bottom;
  x2=x1+dx;
  y2=y1+dy;

  iLine(x1, y1, x2, y1);
  iLine(x2, y1, x2, y2);
  iLine(x2, y2, x1, y2);
  iLine(x1, y2, x1, y1);
}


void iFilledRectangle(double left, double bottom, double dx, double dy) {
  double xx[4], yy[4];
  double x1, y1, x2, y2;

  x1 = left;
  y1 = bottom;
  x2=x1+dx;
  y2=y1+dy;

  xx[0]=x1;
  yy[0]=y1;
  xx[1]=x2;
  yy[1]=y1;
  xx[2]=x2;
  yy[2]=y2;
  xx[3]=x1;
  yy[3]=y2;

  iFilledPolygon(xx, yy, 4);
}

void iFilledCircle(double x, double y, double r, int slices) {
  double t, PI=acos(-1.0), dt, x1,y1, xp, yp;

  if (slices < 0) {
    slices = 100;
  }

  dt = 2*PI/slices;
  xp = x+r;
  yp = y;
  glBegin(GL_POLYGON);
  for(t = 0; t <= 2*PI; t+=dt)
  {
    x1 = x + r * cos(t);
    y1 = y + r * sin(t);

    glVertex2f((GLfloat) xp, (GLfloat) yp);
    xp = x1;
    yp = y1;
  }
  glEnd();
}


void iCircle(double x, double y, double r, int slices) {
  double t, PI=acos(-1.0), dt, x1,y1, xp, yp;

  if (slices < 0) {
    slices = 100;
  }

  dt = 2*PI/slices;
  xp = x+r;
  yp = y;
  for(t = 0; t <= 2*PI; t+=dt)
  {
    x1 = x + r * cos(t);
    y1 = y + r * sin(t);
    iLine(xp, yp, x1, y1);
    xp = x1;
    yp = y1;
  }
}

void iEllipse(double x, double y, double a, double b, int slices) {
  double t, PI=acos(-1.0), dt, x1,y1, xp, yp;

  if (slices < 0) {
    slices = 100;
  }

  dt = 2*PI/slices;
  xp = x+a;
  yp = y;
  for(t = 0; t <= 2*PI; t+=dt)
  {
    x1 = x + a * cos(t);
    y1 = y + b * sin(t);
    iLine(xp, yp, x1, y1);
    xp = x1;
    yp = y1;
  }
}


void iFilledEllipse(double x, double y, double a, double b, int slices) {
  double t, PI=acos(-1.0), dt, x1,y1, xp, yp;


  if (slices < 0) {
    slices = 100;
  }


  dt = 2*PI/slices;
  xp = x+a;
  yp = y;
  glBegin(GL_POLYGON);
  for(t = 0; t <= 2*PI; t+=dt)
  {
    x1 = x + a * cos(t);
    y1 = y + b * sin(t);
    glVertex2f((GLfloat) xp, (GLfloat) yp);
    xp = x1;
    yp = y1;
  }
  glEnd();
}

/*
 Rotates the co-ordinate system
 Parameters:
  (x, y) - The pivot point for rotation
  degree - degree of rotation

 After calling iRotate(), every subsequent rendering will
 happen in rotated fashion. To stop rotation of subsequent rendering,
 call iUnRotate(). Typical call pattern would be:
    iRotate();
    Render your objects, that you want rendered as rotated
    iUnRotate();
*/

void iRotate(double x, double y, double degree) {
  /* push the current matrix stack   */
  glPushMatrix();

  /* The below steps take effect in reverse order   */

  /* step 3: undo the translation   */
  glTranslatef((GLfloat) x, (GLfloat) y, 0.0);

  /* step 2: rotate the co-ordinate system across z-axis   */
  glRotatef((GLfloat) degree, 0, 0, 1.0);

  /* step 1: translate the origin to (x, y)   */
  glTranslatef((GLfloat) -x, (GLfloat) -y, 0.0);
}



void iUnRotate(void) {
  glPopMatrix();
}

void iSetColor(double r, double g, double b) {
  double mmx;
  mmx = r;
  if(g > mmx)mmx = g;
  if(b > mmx)mmx = b;
  mmx = 255;
  if(mmx > 0){
    r /= mmx;
    g /= mmx;
    b /= mmx;
  }
  glColor3f((GLfloat) r, (GLfloat) g, (GLfloat) b);
}


void iDelay(int sec) {
  unsigned long t1, t2;
  t1 = (unsigned long) time(0);
  while(1){
    t2 = (unsigned long) time(0);
    if(t2-t1>=(unsigned long) sec)
      break;
  }
}

void iClear(void) {
  glClear(GL_COLOR_BUFFER_BIT) ;
  glMatrixMode(GL_MODELVIEW) ;
  glClearColor(0,0,0,0);
  glFlush();
}

void displayFF(void) {

  iDraw();
  glutSwapBuffers() ;
}

void animFF(void) {
  if(ifft == 0){
    ifft = 1;
    iClear();
  }
  glutPostRedisplay();
}


void keyboardHandler1FF(unsigned char key, int x, int y) {
  iKeyboard(key);
  glutPostRedisplay();
}

void keyboardHandler2FF(int key, int x, int y) {
  iSpecialKeyboard((unsigned char) key);
  glutPostRedisplay();
}

void mouseMoveHandlerFF(int mx, int my) {
  mouseX = mx;
  mouseY = iScreenHeight - my;
  iMouseMove(IMOUSE_DRAGGED);

  glFlush();
}

void mousePassiveMoveHandlerFF(int mx, int my) {
  mouseX = mx;
  mouseY = iScreenHeight - my;
  iMouseMove(IMOUSE_MOVED);

  glFlush();
}

void mouseHandlerFF(int button, int state, int x, int y) {
  mouseX = x;
  mouseY = iScreenHeight - y;

  iMouse(button, state, mouseX, mouseY);

  glFlush();
}

void resize(int width, int height) {
  glutReshapeWindow(iScreenWidth, iScreenHeight);
}

void iInitialize(int width, int height, char const * title) {
  iScreenHeight = height;
  iScreenWidth = width;

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA) ;
  glutInitWindowSize(width , height ) ;
  glutInitWindowPosition( 10 , 10 ) ;
  glutCreateWindow(title) ;
  glutReshapeFunc(resize);
  glClearColor( 0.0 , 0.0 , 0.0 , 0.0 ) ;
  glMatrixMode( GL_PROJECTION) ;
  glLoadIdentity() ;
  glOrtho(0.0 , width , 0.0 , height , -1.0 , 1.0) ;
  /* glOrtho(-100.0 , 100.0 , -100.0 , 100.0 , -1.0 , 1.0) ; */
  /* SetTimer(0, 0, 10, timer_proc); */

  iClear();

  glutDisplayFunc(displayFF) ;
  glutKeyboardFunc(keyboardHandler1FF); /*normal*/
  glutSpecialFunc(keyboardHandler2FF); /*special keys*/
  glutMouseFunc(mouseHandlerFF);
  glutMotionFunc(mouseMoveHandlerFF);
  glutPassiveMotionFunc(mousePassiveMoveHandlerFF);
  glutIdleFunc(animFF) ;

  /*
  Setup Alpha channel testing.
  If alpha value is greater than 0, then those
  pixels will be rendered. Otherwise, they would not be rendered
  */
  glAlphaFunc(GL_GREATER,0.0f);
  glEnable(GL_ALPHA_TEST);

  glutMainLoop();
}


int iWidth(void) {
  return iScreenWidth;
}

int iHeight(void) {
  return iScreenHeight;
}


int iMouseX(void) {
  return mouseX;
}

int iMouseY(void) {
  return mouseY;
}

