#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#include <windows.h>
#include "MyStructs.h"

// Particle functions
void Brush(POINT2D centerPoint, int brushSize, COLOR color);
void DrawPoint(POINT2D point, COLOR color);
void DrawCircle(POINT2D centerPoint, POINT2D outerPoint, COLOR color);
void ParticlesToPixels();

// Pixel/Color functions
int ColorCompare(COLOR color1, COLOR color2);
COLOR ColorAtPoint(POINT2D point);
void FillRand();
void FillSolid(COLOR color);

// Point functions
int PointInWindow(POINT2D point);
float PointDistance(POINT2D point1, POINT2D point2);

// Updates
void WindowProperties();
void Input(MSG message);
void PhysUpdate();

#endif