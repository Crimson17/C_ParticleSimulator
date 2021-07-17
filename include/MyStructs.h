#ifndef MYSTRUCTS_H
#define MYSTRUCTS_H

#include <windows.h>

typedef unsigned char BYTE;

typedef struct RGBColor {
    BYTE r;
    BYTE g;
    BYTE b;
}COLOR;

// Particle
typedef struct Particle {
    COLOR color;
    int updated;
    double velocity;
}PARTICLE;

typedef struct Point2D {
    int x;
    int y;
}POINT2D;

// Global variables
extern int globalRunning;
extern int windowWidth;
extern int windowHeight;
extern int hideConsole;
extern int brushSize;
extern int particleCount;
extern BYTE* pixels;
extern PARTICLE* particles;
extern BITMAPINFO bitmap_info;
extern COLOR backgroundColor;

// Main screen size
#define ScreenX GetSystemMetrics(SM_CXSCREEN)
#define ScreenY GetSystemMetrics(SM_CYSCREEN)

#endif
