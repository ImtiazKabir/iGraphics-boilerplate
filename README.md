# IGRAPHICS BOILERPLATE
A sample igraphics boilerplate


## Usage
First clone this repository or simply download it as a zip and then extract it. Currently we support 2 main editors/ide. But you can use any editor and then build the project from terminal. First of all, make sure you have `mingw32` installed in `C:\MinGW\MinGW` directory (make sure `C:\MinGW\MinGW\bin` exists)

You will find a `setpath.bat` file in the project directory. Run that as adminstrator. This is a one time process. You do **NOT** need to run this file every single time.


## For Codeblocks users
Simply open the `template.cbp` file with Codeblocks. Use the buttons from the toolbar to build and run the project.

## For VS Code users
VS code users can open the entire project directory with VS code. To build the project, press `Ctrl+Shift+B` and to run it, press `Ctrl+F5`

## For others
Other editor users / terminal lovers can build the project by running the following command from command prompt or powershell
```
mingw32-make.exe
```
and to run the project enter this command
```
mingw32-make.exe run
```


## File structure
The main source codes are kept inside `src` folder. The entry point of this project is `src/main.c`

If you want to create multiple files, then put your `.c` files in the `src` folder and put your header files(`.h`) in `include` folder. You do **NOT** need to put a relative path while including a library. For example if you want to include `include/kitty.h` from your `src/foo.c` then simply include it like this -
```c
#include "kitty.h"
```
Notice how the relative path from `src` to `include` is omitted.

### Images/sound (assets)
Assets are to be kept inside the `assets/` folder. (*Not to confuse with `bin/assets`*)
Let's say you want to show `assets/kitty.bmp` from your `src/foo.c`. Use it like so - 
```c
iShowBMP(x, y, "assets/kitty.bmp");
```
Notice how you are having it to type in the full path for an asset.


## Must declare functions and MACROS
### The `main` function
The `main` function has 2 key parts for the user to edit.
1. The initialization for the global variables
2. The cleanup code

The first part is before `iSetTimer` is called. Here you initialize all the global variables.

And the second part is after `iInitialize` is called. Here you should write your cleanup code. You are suggested to free the pointers allocated at the heap in this segment.

### The `iDraw` function
This is where you draw all your fancy stuff. This function is supposed to be used only for drawing. You **should not** update your variables here. That's where the `update` function comes in

### The `update` function
This function is called periodically. All your update-logic should be contained in this function.

### The `iMouseMove` function
This function is triggered every single time the mouse is moved. It takes a `state` parameter which can have 2 values - `IMOUSE_MOVED` or `IMOUSE_DRAGGED`. If the mouse is moved without dragging then `state = IMOUSE_MOVED`. Otherwise `state = IMOUSE_DRAGGED`

### The `iKeyboard` and the `iSpecialKeyboard` function
Both function is for listening to keyboard events.

The `iSpecialKeyboard` function is triggerd when some special key (like function keys - `F1`, `F2` etc) are pressed.

For other normal keypress events,  `iKeyboard` is triggered.

Both function takes `unsigned char key` as a parameter. For `iKeyboard` it is just the character expression of the key (like `'a'`, `'b'` etc). But for `iSpecialKeyboard` the value of `char` is an enum defined in openGL library.

### The `FPS` macro
This controls the "frames per second" for the project. This does not affect the `iDraw` cycle. It just limits your `update` cycle to follow the `FPS` value

### The `WIDTH` and `HEIGHT` macro
These macros define the resolution of the screen. **You are advised to avoid using them whenever you can**. Use `iWidth()` and `iHeight()` if possible.

These macros are for cases where `iWidth()` and `iHeight()` are not ready yet (specifically speaking, before `iInitialize` is called).

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

The parameter `slices` is the number of slices to draw an ellipse or a circle. The more the `slices` the smoother the shape, but the slower the runtime! If you want to use the default behaviour of iGraphics then pass `-1` in place of `slices`

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