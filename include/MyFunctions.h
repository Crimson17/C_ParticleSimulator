#include "..\include\MyStructs.h"

#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

// Functions included in MyMain.c
void WindowProperties();
int MyMain(void);
void FrameUpdate(MSG message);

// Functions needed for window creation
LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

// Pixel functions
void PixelsFillRand(unsigned int *pixelMemory, int memoryLength);
void PixelsFillSolid(unsigned int *pixelMemory, int memoryLength, int color);
void PixelsDrawLine(unsigned int *pixelMemory, POINT2D point1, POINT2D point2, int color);
void PixelsDrawTriangle(unsigned int *pixelMemory, POINT2D point1, POINT2D point2, POINT2D point3, int color);

// Vector functions
VECTOR2D Vector_New(POINT2D point1, POINT2D point2);
VECTOR2D Vector_Normalize(VECTOR2D inputVector);
float Vector_Length(VECTOR2D inputVector);
void Vector_Print(VECTOR2D inputVector);

#endif