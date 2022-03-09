#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include "MyStructs.h"
#include "MyFunctions.h"


// Switches places of 2 given particles
void SwitchParticles(POINT2D firstParticle, POINT2D secondParticle) {
    PARTICLE tempParticle = *(particles + (firstParticle.y * windowWidth) + firstParticle.x);
    *(particles + (firstParticle.y * windowWidth) + firstParticle.x) = *(particles + (secondParticle.y * windowWidth) + secondParticle.x);
    *(particles + (secondParticle.y * windowWidth) + secondParticle.x) = tempParticle;
    //(particles + (secondParticle.y * windowWidth) + secondParticle.x)->updated = 1;
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
void DrawCircle(POINT2D centerPoint, double radius, COLOR color)
{
    double degreeStep = (360.0 / ((2 * radius * M_PI) * 10.0));
    for (double degrees = 0.0; degrees < 360.0; degrees += degreeStep) {
        DrawPoint((POINT2D) { centerPoint.x + (radius * sin(degrees)), centerPoint.y + (radius * cos(degrees)) }, color);
    }
}

// Draws a custom colored big dot on the given point
void Brush(POINT2D centerPoint, int brushSize, COLOR color) {
    for (int i = 1; i <= brushSize; i++) {
        DrawCircle(centerPoint, i, color);
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

// Returns decimal time
double RawTimeVal(struct timeval startTime, struct timeval endTime, int returnType) {
    long differenceInSeconds = endTime.tv_sec - startTime.tv_sec;
    long differenceInMicroseconds = endTime.tv_usec - startTime.tv_usec;
    // Time in seconds
    if (returnType == 2) {
        return (differenceInSeconds + (differenceInMicroseconds / 1000000.0));
    }
    // Time in miliseconds
    if (returnType == 1) {
        return ((differenceInSeconds * 1000.0) + (differenceInMicroseconds / 1000.0));
    }
    // Time in microseconds
    if (returnType == 0) {
        return ((differenceInSeconds * 1000000.0) + differenceInMicroseconds);
    }
    return 0.0;
}
