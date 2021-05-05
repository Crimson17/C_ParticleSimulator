#include <windows.h>

#ifndef GLOBALVARS_H
#define GLOBALVARS_H

// Global variables
int globalRunning;
int _windowWidth;
int _windowHeight;
int _backgroundColor;
float _fps;
int _hideConsole;
int _brushSize;
unsigned int *_pixelMemory;
int _pixelMemoryLen;
BITMAPINFO bitmap_info;

// Main screen size
#define ScreenX GetSystemMetrics(SM_CXSCREEN)
#define ScreenY GetSystemMetrics(SM_CYSCREEN)

// Color macros
#define _ColorBlack 0x000000
#define _ColorWhite 0xFFFFFF
#define _ColorRed 0xFF0000
#define _ColorRedDark 0x770000
#define _ColorGreen 0x00FF00
#define _ColorGreenDark 0x007700
#define _ColorBlue 0x0000FF
#define _ColorBlueDark 0x000077
#define _ColorYellow 0xFFEE00
#define _ColorOrange 0xFF9900
#define _ColorCyan 0x00CC99
#define _ColorMagenta 0xFF00FF
#define _ColorBrown 0x804000
#define _ColorGray 0x7D7D7D
#define _ColorKrimzoFav 0x112233

#endif