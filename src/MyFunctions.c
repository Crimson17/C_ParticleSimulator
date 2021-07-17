#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include "MyFunctions.h"
#include "MyStructs.h"
#include "MyThreading.h"


// Recolor all pixels to particles, RED and BLUE channels need to be switched because it's 24bit color
void ParticlesToPixelsParallel(int i){
    *(pixels + 3 * i) = (particles + i)->color.b;
    *(pixels + 3 * i + 1) = (particles + i)->color.g;
    *(pixels + 3 * i + 2) = (particles + i)->color.r;
    (particles + i)->updated = 0;
}

void ParticlesToPixels() {
    ParallelFor(0, particleCount, 4, ParticlesToPixelsParallel);
    /*
    for (int i = 0; i < particleCount; i++) {
        *(pixels + 3 * i) = (particles + i)->color.b;
        *(pixels + 3 * i + 1) = (particles + i)->color.g;
        *(pixels + 3 * i + 2) = (particles + i)->color.r;
        (particles + i)->updated = 0;
    }
    */
}

// Compares 2 colors
int ColorCompare(COLOR color1, COLOR color2) {
    if (color1.r != color2.r) {
        return 0;
    }
    if (color1.g != color2.g) {
        return 0;
    }
    if (color1.b != color2.b) {
        return 0;
    }
    return 1;
}

// Returns a color at the point
COLOR ColorAtPoint(POINT2D point) {
    return (particles + point.x + (point.y * windowWidth))->color;
}

// Sets a color to the particle
void DrawPoint(POINT2D point, COLOR color)
{
    if (PointInWindow(point)) {
        (particles + point.x + (point.y * windowWidth))->color = color;
    }
}

// Draws a custom colored circle on the window with the given points
void DrawCircle(POINT2D centerPoint, POINT2D outerPoint, COLOR color)
{
    float radius = PointDistance(centerPoint, outerPoint);
    float circleCirc = 2 * radius * M_PI;
    float degreeStep = (360.0 / (circleCirc * 10.0));
    // Loop for dot travel
    for (float degrees = 0; degrees < 360.0; degrees += degreeStep) {
        POINT2D travelDot = { centerPoint.x + (radius * sin(degrees)), centerPoint.y + (radius * cos(degrees)) };
        DrawPoint(travelDot, color);
    }
}

// Draws a custom colored big dot on the given point
void Brush(POINT2D centerPoint, int brushSize, COLOR color) {
    for (int i = 0; i < brushSize; i++) {
        POINT2D tempPoint = { centerPoint.x + i + 1, centerPoint.y };
        DrawCircle(centerPoint, tempPoint, color);
    }
}

// Fill memory with random colors
void FillRand()
{
    for (int i = 0; i < particleCount; i++) {
        (particles + i)->color = (COLOR){ rand() % 256, rand() % 256, rand() % 256 };
    }
}

// Fill memory with a single color
void FillSolid(COLOR color)
{
    for (int i = 0; i < particleCount; i++) {
        (particles + i)->color = color;
    }
}

// Returns true if point is inside the window
int PointInWindow(POINT2D point)
{
    if (point.x < 0 || point.x > windowWidth - 1) {
        return 0;
    }
    if (point.y < 0 || point.y > windowHeight - 1) {
        return 0;
    }
    return 1;
}

// Returns a distance between 2 points
float PointDistance(POINT2D point1, POINT2D point2) {
    return (sqrt(pow((point2.x - point1.x), 2) + pow((point2.y - point1.y), 2)));
}
