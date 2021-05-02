#include <windows.h>

#ifndef GLOBALVARS_H
#define GLOBALVARS_H

int globalRunning;
int windowWidth;
int windowHeight;
void *pixelMemory;
BITMAPINFO bitmap_info;

#endif

// Color macros
#define ColorBlack 0x000000
#define ColorWhite 0xFFFFFF
#define ColorRed 0xFF0000
#define ColorRedDark 0x770000
#define ColorGreen 0x00FF00
#define ColorGreenDark 0x007700
#define ColorBlue 0x0000FF
#define ColorBlueDark 0x000077
#define ColorYellow 0xFFEE00
#define ColorOrange 0xFF9900
#define ColorCyan 0x00CC99
#define ColorMagenta 0xFF00FF
#define ColorBrown 0x804000
#define ColorGray 0x7D7D7D
#define ColorKrimzoFav 0x112233
