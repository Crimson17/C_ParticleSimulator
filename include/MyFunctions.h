#include "..\include\MyStructs.h"

#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
void PixelsFillRand(unsigned int *pixelMemory, int memoryLength);

#endif