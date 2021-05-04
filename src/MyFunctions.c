#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include "..\include\MyFunctions.h"
#include "..\include\MyStructs.h"
#include "..\include\GlobalVars.h"

// Communicates with windows
LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result;
    switch (message)
    {
    // Stops the window loop if the window message was WM_CLOSE
    case WM_CLOSE:
        globalRunning = 0;
        break;
    default:
        result = DefWindowProc(window, message, wParam, lParam);
        break;
    }
    return result;
}

// Draws a custom colored line on the window with the given points
void PixelsDrawLine(unsigned int *pixelMemory, POINT2D point1, POINT2D point2, int color)
{
    // Check if the coords are inside of the bounds
    if (point1.x < 0 || point2.x < 0 || point1.x > calcWindowWidth || point2.x > calcWindowWidth)
    {
        printf("Point x coordinates are out of range, range.x -> 0 ~ %d\n", calcWindowWidth);
        return;
    }
    if (point1.y < 0 || point2.y < 0 || point1.y > calcWindowHeight || point2.y > calcWindowHeight)
    {
        printf("Point y coordinates are out of range, range.y -> 0 ~ %d\n", calcWindowHeight);
        return;
    }

    // Calculate the vector and normalize to get the direction
    VECTOR2D tempVec = Vector_New(point1, point2);
    float tempVecLen = Vector_Length(tempVec);
    VECTOR2D normVec = Vector_Normalize(tempVec);

    // Divide by 10 to get a better precision (the speed is not important yet..)
    normVec.i /= 10;
    normVec.j /= 10;

    // Basically a dot that travels over the line path and changes the pixel colors
    POINT2D travelDot = {0};
    travelDot.x = point1.x;
    travelDot.y = point1.y;

    // Loop for dot travel
    for (int i = 0; i < (tempVecLen * 10); i++)
    {
        // Change pixel color
        *(pixelMemory + ((int)travelDot.x + ((int)travelDot.y * calcWindowWidth))) = color;
        // Increment dot cords by the normalized vector
        travelDot.x += normVec.i;
        travelDot.y += normVec.j;
    }
}

// Draws a custom colored traingle on the window with the given points
void PixelsDrawTriangle(unsigned int *pixelMemory, POINT2D point1, POINT2D point2, POINT2D point3, int color)
{
    PixelsDrawLine(pixelMemory, point1, point2, color);
    PixelsDrawLine(pixelMemory, point2, point3, color);
    PixelsDrawLine(pixelMemory, point3, point1, color);
}

// Fill memory with randomly colored pixels
void PixelsFillRand(unsigned int *pixelMemory, int memoryLength)
{
    for (int i = 0; i < memoryLength; i++)
    {
        *(pixelMemory + i) = 0 + (float)rand() / RAND_MAX * (16777216); // 0xFFFFFF = 16777215
    }
}

// Fill memory with a single color
void PixelsFillSolid(unsigned int *pixelMemory, int memoryLength, int color)
{
    for (int i = 0; i < memoryLength; i++)
    {
        *(pixelMemory + i) = color;
    }
}

// Creates a new vector from 2 given points
VECTOR2D Vector_New(POINT2D point1, POINT2D point2)
{
    VECTOR2D outputVector = {0};
    outputVector.i = point2.x - point1.x;
    outputVector.j = point2.y - point1.y;
    return outputVector;
}

// Returns a length 1 vector with the same direction as the given vector
VECTOR2D Vector_Normalize(VECTOR2D inputVector)
{
    VECTOR2D outputVector = {0};
    outputVector.i = inputVector.i / Vector_Length(inputVector);
    outputVector.j = inputVector.j / Vector_Length(inputVector);
    return outputVector;
}

// Returns a length of a given vector
float Vector_Length(VECTOR2D inputVector)
{
    return sqrt(pow(inputVector.i, 2) + pow(inputVector.j, 2));
}

// Prints the vector to the terminal
void Vector_Print(VECTOR2D inputVector)
{
    printf("%.2fi + %.2fj\n", inputVector.i, inputVector.j);
}
