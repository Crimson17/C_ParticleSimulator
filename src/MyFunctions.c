#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include "..\include\MyFunctions.h"
#include "..\include\MyStructs.h"
#include "..\include\GlobalVars.h"

// Communicates with windows, when yuo click on "X" windows sends a WM_CLOSE message
LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result;
    switch (message)
    {
    case WM_CLOSE:
        globalRunning = 0;
        break;

    default:
        result = DefWindowProc(window, message, wParam, lParam);
        break;
    }
    return result;
}

// Fill memory with randomly colored pixels
void PixelsFillRand(unsigned int *_pixelMemory, int memoryLength)
{
    for (int i = 0; i < memoryLength; i++)
    {
        *(_pixelMemory + i) = 0 + (float)rand() / RAND_MAX * (16777216); // 0xFFFFFF = 16777215
    }
}
