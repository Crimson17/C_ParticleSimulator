#include <windows.h>
#include "..\include\Structures.h"

#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

// Functions included in MyMain.c
void WindowProperties();
int MyMain(void);
void FrameUpdate(MSG message);
void PhysUpdate();

// Functions needed for window creation
LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

// Pixel functions
unsigned int ColorAtPoint(POINT2D point);
void PixelsBrush(POINT2D centerPoint, int brushSize, int color);
void PixelsDrawPoint(POINT2D point, int color);
void PixelsDrawLine(POINT2D point1, POINT2D point2, int color);
void PixelsDrawTriangle(POINT2D point1, POINT2D point2, POINT2D point3, int color);
void PixelsDrawRectangle(POINT2D point1, POINT2D point2, int color);
void PixelsDrawCircle(POINT2D centerPoint, POINT2D outerPoint, int color);
void PixelsVerticalMask(int color);
void PixelsHorizontalMask(int color);
void PixelsFillRand();
void PixelsFillSolid(int color);

// Point functions
float Point2D_Distance(POINT2D point1, POINT2D point2);
int PointInWindow(POINT2D point);

// Vector functions
VECTOR2D Vector_New(POINT2D point1, POINT2D point2);
VECTOR2D Vector_Normalize(VECTOR2D inputVector);
float Vector_Length(VECTOR2D inputVector);
void Vector_Print(VECTOR2D inputVector);

#endif