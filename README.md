# IGRAPHICS BOILERPLATE
A sample igraphics boilerplate

## Docs

### Initialize the window and thus start the draw loop
```c
void iInitialize(int width, int height, char const *title);
```
Calling this function starts the draw loop

### Get resolution of the screen
```c
int iWidth(void);
int iHeight(void);
```
It is recommended to use these functions to get the width and height of the screen whenever possible. But there might be some cases where the width and height are not ready yet. In those cases use the `WIDTH` and `HEIGHT` macros defined in the `src/main.c`

### Get the mouse position
```c
int iMouseX(void);
int iMouseY(void);
```
These variables are automatically updated for you whenever the mouse moves. Simply call them to get the current position of the mouse


### Set and get color
```c
void iSetColor(double r, double g, double b);
void iGetPixelColor(int x, int y, int rgb[]);
```
The rgb values range from `0` to `255` in both cases. The set color method sets the color of the "brush" with the given red, green and blue value.

The get color method expects the position of the pixel to extract color from as `x`, `y` coordinates. It takes an array to write the rgb value on as `int rgb[]`. The array should have a length of 3. The get color method can be used like this -
```c
int rgb[3], red, green, blue;
iGetPixelColor(50, 10, rgb);
red = rgb[0];
green = rgb[1];
blue = rgb[2];
/* Now do stuff with these extracted color values */
```

### Display text
```c
void iText(double x, double y, char const *str, void *font);
```
- `x` and `y` are the coordinate values to display the text
- `str` is the string to display
- `font` is the openGL enum of the font. If the default font of iGraphics is desired then simply pass `0` in place of `*font`


### Draw basic shapes
```c
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
```

### Clear the screen
```c
void iClear(void);
```
The clear function clears the screen with a black color. If you 
want to draw some other color than black then simply draw a filled rectangle of that desired color. That rectangle must have the same size as the screen. For example - 
```c
iSetColor(r, g, b);
iFilledRectangle(0, 0, iWidth(), iHeight());
```

### Rotate the axes with some angle by a known point and undo a rotation
```c
void iRotate(double x, double y, double degree);
void iUnRotate(void);
```

### Delay some seconds
```c
void iDelay(int sec);
```

### Show a bitmap image on screen
```c
void iShowBMP(int x, int y, char const *filename);
void iShowBMP2(int x, int y, char const *filename, int ignoreColor); 
```
These functions show a bitmap file mentioned by the string, `filename`. Here `x` and `y` represents the bottom-left corner's coordinate of the image. Note that `iShowBMP2` is a superset of `iShowBMP`. If you want to get a black and white iamge, call `ishowBMP2` with `ignoreColor` set to `1`. Otherwise, call `iShowBMP`. For example -
```c
iShowBMP(45, 23, "assets/ball.bmp");
```

### Set, pause and resume timer
```c
int iSetTimer(int msec, void (*f)(void));
void iPauseTimer(int index);
void iResumeTimer(int index);
```
Timers are used to call a function periodically. `iSetTimer` takes 2 parameters - 
- `msec` : The period in milliseconds
- The pointer to the function to call after each period. The pointer to the function can be obtained by using simply the name of the function

**One can have at best 10 timers**

`iPauseTimer` and `iResumeTimer` takes the index of the timer to operate on