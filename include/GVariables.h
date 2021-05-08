#include <windows.h>

#ifndef GLOBALVARS_H
#define GLOBALVARS_H

// Global variables
int _globalRunning;
int _windowWidth;
int _windowHeight;
int _backgroundColor;
int _hideConsole;
int _brushSize;
unsigned int *_pixels;
PARTICLE *_particles;
int _memoryLen;
BITMAPINFO _bitmap_info;

// Main screen size
#define ScreenX GetSystemMetrics(SM_CXSCREEN)
#define ScreenY GetSystemMetrics(SM_CYSCREEN)

#endif