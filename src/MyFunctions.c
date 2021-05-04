#define _USE_MATH_DEFINES
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

// Draws a custom colored pixel
void PixelsDrawPoint(unsigned int *pixelMemory, POINT2D point, int color)
{
    *(pixelMemory + ((int)point.x + ((int)point.y * calcWindowWidth))) = color;
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
        PixelsDrawPoint(pixelMemory, travelDot, color);
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

void PixelsDrawCircle(unsigned int *pixelMemory, POINT2D centerPoint, POINT2D outerPoint, int color)
{
    float radius = Point2D_Distance(centerPoint, outerPoint);
    if (centerPoint.x - radius >= 0 && centerPoint.x + radius <= calcWindowWidth && centerPoint.y >= 0 && centerPoint.y <= calcWindowHeight)
    {
        float circleCirc = 2 * radius * M_PI;
        float degreeStep = (360.0 / (circleCirc * 10.0));
        for (float degrees = 0; degrees < 360.0; degrees += degreeStep)
        {
            POINT2D travelDot = {centerPoint.x + (radius * sin(degrees)), centerPoint.y + (radius * cos(degrees))};
            PixelsDrawPoint(pixelMemory, travelDot, color);
        }
    }
}

// Draws a vertical mask over the whole screen
void PixelsVerticalMask(unsigned int *pixelMemory, int color)
{
    for (int i = 0; i < calcWindowWidth; i += 2)
    {
        PixelsDrawLine(pixelMemory, (POINT2D){i, 0}, (POINT2D){i, calcWindowHeight}, color);
    }
}

// Draws a horizontal mask over the whole screen
void PixelsHorizontalMask(unsigned int *pixelMemory, int color)
{
    for (int i = 0; i < calcWindowHeight; i += 2)
    {
        PixelsDrawLine(pixelMemory, (POINT2D){0, i}, (POINT2D){calcWindowWidth, i}, color);
    }
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

// Returns a distance between 2 points
float Point2D_Distance(POINT2D point1, POINT2D point2)
{
    return (sqrt(pow((point2.x - point1.x), 2) + pow((point2.y - point1.y), 2)));
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
