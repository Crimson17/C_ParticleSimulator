#include "..\include\MyStructs.h"

#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
void PixelsFillRand(unsigned int *pixelMemory, int memoryLength);
void PixelsFillSolid(unsigned int *_pixelMemory, int memoryLength, int color);
void PixelsDrawLine(unsigned int *_pixelMemory, POINT2D point1, POINT2D point2, int color);

#endif