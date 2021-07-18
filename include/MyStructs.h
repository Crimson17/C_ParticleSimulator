#ifndef MYSTRUCTS_H
#define MYSTRUCTS_H

#include <windows.h>

typedef unsigned char BYTE;

// RGB color
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

// Point in 2D space
typedef struct Point2D {
    int x;
    int y;
}POINT2D;

// Global variables
extern BYTE ANDmaskIcon[128];
extern BYTE XORmaskIcon[128];
extern int globalRunning;
extern double deltaTime;
extern double gravity;
extern int windowWidth;
extern int windowHeight;
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
