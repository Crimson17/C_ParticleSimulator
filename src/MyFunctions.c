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

void PixelsDrawLine(unsigned int *_pixelMemory, POINT2D point1, POINT2D point2, int color)
{
    VECTOR2D tempVec = Vector_New(point1, point2);
    float tempVecLength = Vector_Length(tempVec);

    VECTOR2D normVec = Vector_Normalize(tempVec);

    VECTOR2D drawerVec = {0};
    drawerVec.i = point1.x;
    drawerVec.j = point1.y;

    while (Vector_Length(drawerVec) < tempVecLength)
    {
        *(_pixelMemory + ((int)drawerVec.i + ((int)drawerVec.j * windowWidth))) = color;
        drawerVec.i += normVec.i;
        drawerVec.j += normVec.j;
    }
}

// Fill memory with randomly colored pixels
void PixelsFillRand(unsigned int *_pixelMemory, int memoryLength)
{
    for (int i = 0; i < memoryLength; i++)
    {
        *(_pixelMemory + i) = 0 + (float)rand() / RAND_MAX * (16777216); // 0xFFFFFF = 16777215
    }
}

// Fill memory with a single color
void PixelsFillSolid(unsigned int *_pixelMemory, int memoryLength, int color)
{
    for (int i = 0; i < memoryLength; i++)
    {
        *(_pixelMemory + i) = color;
    }
}

VECTOR2D Vector_New(POINT2D point1, POINT2D point2)
{
    VECTOR2D outputVector = {0};
    outputVector.i = point2.x - point1.x;
    outputVector.j = point2.y - point1.y;
    return outputVector;
}

VECTOR2D Vector_Normalize(VECTOR2D inputVector)
{
    VECTOR2D outputVector = {0};
    outputVector.i = inputVector.i / Vector_Length(inputVector);
    outputVector.j = inputVector.j / Vector_Length(inputVector);
    return outputVector;
}

float Vector_Length(VECTOR2D inputVector)
{
    return sqrt(pow(inputVector.i, 2) + pow(inputVector.j, 2));
}

void Vector_Print(VECTOR2D inputVector)
{
    printf("%.2fi + %.2fj\n", inputVector.i, inputVector.j);
}
