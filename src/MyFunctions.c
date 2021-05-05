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
    case WM_CHAR:
        if(wParam == 27){
            globalRunning = 0;
        }
        break;
    default:
        result = DefWindowProc(window, message, wParam, lParam);
        break;
    }
    return result;
}

// Returns a color at the point
unsigned int ColorAtPoint(POINT2D point){
    return *(_pixelMemory + ((int)point.x + ((int)point.y * _windowWidth)));
}

void PixelsBrush(POINT2D centerPoint, int brushSize, int color){
    for(int i=0; i<brushSize; i++){
        POINT2D tempPoint = {centerPoint.x + i + 1, centerPoint.y};
        PixelsDrawCircle(centerPoint, tempPoint, color);
    }
}

// Draws a custom colored pixel
void PixelsDrawPoint(POINT2D point, int color)
{
    *(_pixelMemory + ((int)point.x + ((int)point.y * _windowWidth))) = color;
}

// Draws a custom colored line on the window with the given points
void PixelsDrawLine(POINT2D point1, POINT2D point2, int color)
{
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
        // Check if point is in the window and change pixel color if is
        if (PointInWindow(travelDot))
        {
            PixelsDrawPoint(travelDot, color);
        }
        // Increment dot cords by the normalized vector
        travelDot.x += normVec.i;
        travelDot.y += normVec.j;
    }
}

// Draws a custom colored traingle on the window with the given points
void PixelsDrawTriangle(POINT2D point1, POINT2D point2, POINT2D point3, int color)
{
    PixelsDrawLine(point1, point2, color);
    PixelsDrawLine(point2, point3, color);
    PixelsDrawLine(point3, point1, color);
}

// Draws a custom colored rectangle on the window with the given points
void PixelsDrawRectangle(POINT2D point1, POINT2D point2, int color){
    POINT2D tempPoint1 = {point1.x, point2.y};
    POINT2D tempPoint2 = {point2.x, point1.y};
    PixelsDrawLine(point1, tempPoint1, color);
    PixelsDrawLine(point1, tempPoint2, color);
    PixelsDrawLine(tempPoint1, point2, color);
    PixelsDrawLine(tempPoint2, point2, color);
}

// Draws a custom colored circle on the window with the given points
void PixelsDrawCircle(POINT2D centerPoint, POINT2D outerPoint, int color)
{
    float radius = Point2D_Distance(centerPoint, outerPoint);
    float circleCirc = 2 * radius * M_PI;
    float degreeStep = (360.0 / (circleCirc * 10.0));
    // Loop for dot travel
    for (float degrees = 0; degrees < 360.0; degrees += degreeStep)
    {
        POINT2D travelDot = {centerPoint.x + (radius * sin(degrees)), centerPoint.y + (radius * cos(degrees))};
        if (PointInWindow(travelDot))
        {
            PixelsDrawPoint(travelDot, color);
        }
    }
}

// Draws a vertical mask over the whole screen
void PixelsVerticalMask(int color)
{
    for (int i = 0; i < _windowWidth; i += 2)
    {
        POINT2D tempPoint1 = {i, 0};
        POINT2D tempPoint2 = {i, _windowHeight};
        PixelsDrawLine(tempPoint1, tempPoint2, color);
    }
}

// Draws a horizontal mask over the whole screen
void PixelsHorizontalMask(int color)
{
    for (int i = 0; i < _windowHeight; i += 2)
    {
        POINT2D tempPoint1 = {0, i};
        POINT2D tempPoint2 = {_windowWidth, i};
        PixelsDrawLine(tempPoint1, tempPoint2, color);
    }
}

// Fill memory with randomly colored pixels
void PixelsFillRand()
{
    for (int i = 0; i < _pixelMemoryLen; i++)
    {
        *(_pixelMemory + i) = 0 + (float)rand() / RAND_MAX * (16777216); // 0xFFFFFF = 16777215
    }
}

// Fill memory with a single color
void PixelsFillSolid(int color)
{
    for (int i = 0; i < _pixelMemoryLen; i++)
    {
        *(_pixelMemory + i) = color;
    }
}

// Returns a distance between 2 points
float Point2D_Distance(POINT2D point1, POINT2D point2)
{
    return (sqrt(pow((point2.x - point1.x), 2) + pow((point2.y - point1.y), 2)));
}

// Returns true if point is inside the window
int PointInWindow(POINT2D point)
{
    if (point.x < 0 || point.x > _windowWidth-1)
    {
        return 0;
    }
    if (point.y < 0 || point.y > _windowHeight-1)
    {
        return 0;
    }
    return 1;
}

// Creates a new vector from 2 given points
VECTOR2D Vector_New(POINT2D point1, POINT2D point2)
{
    VECTOR2D outputVector = {point2.x - point1.x, point2.y - point1.y};
    return outputVector;
}

// Returns a length 1 vector with the same direction as the given vector
VECTOR2D Vector_Normalize(VECTOR2D inputVector)
{
    VECTOR2D outputVector = {inputVector.i / Vector_Length(inputVector), inputVector.j / Vector_Length(inputVector)};
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
