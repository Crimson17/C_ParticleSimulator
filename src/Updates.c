#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <stdint.h>
#include "MyStructs.h"
#include "Materials.h"
#include "MyFunctions.h"


// Handles window input
int solidMaterialExists = 0;
int counter = 0;
void Input(MSG message)
{
    // Check for left mouse button
    if (message.wParam == 1) {
        POINT2D mouseCoords = { LOWORD(message.lParam), abs(HIWORD(message.lParam) - windowHeight) };
        Brush(mouseCoords, brushSize, _MaterialSand);
    }
    // Check for right mouse button
    else if (message.wParam == 2) {
        POINT2D mouseCoords = { LOWORD(message.lParam), abs(HIWORD(message.lParam) - windowHeight) };
        Brush(mouseCoords, brushSize, _MaterialWater);
    }
    // Check for middle mouse button
    else if (message.wParam == 16) {
        POINT2D mouseCoords = { LOWORD(message.lParam), abs(HIWORD(message.lParam) - windowHeight) };
        Brush(mouseCoords, brushSize, _MaterialRockSolid);
        solidMaterialExists = 1;
    }
    // Check for spacebar
    else if (message.wParam == ' ' && solidMaterialExists) {
        for (int i = 0; i < particleCount; i++) {
            if (ColorCompare((particles + i)->color, _MaterialRockSolid)) {
                (particles + i)->color = _MaterialRockParticle;
            }
        }
        solidMaterialExists = 0;
    }
    // Check for R
    else if (message.wParam == 'r') {
        for (int i = 0; i < particleCount; i++) {
            (particles + i)->color = backgroundColor;
            //(particles + i)->updated = 0;
            //(particles + i)->velocity = 0.0;
        }
        solidMaterialExists = 0;
    }
}

// Update particle physics
int frameSide = 1;
void PhysUpdate1(int i) {
    POINT2D tempPoint = { i % windowWidth, i / windowWidth };
    if (ColorCompare(ColorAtPoint(tempPoint), _MaterialSand)) {
        MaterialLogicSand(tempPoint);
    }
    else if (ColorCompare(ColorAtPoint(tempPoint), _MaterialWater)) {
        MaterialLogicWater(tempPoint);
    }
    else if (ColorCompare(ColorAtPoint(tempPoint), _MaterialRockParticle)) {
        MaterialLogicRockParticle(tempPoint);
    }
}
void PhysUpdate2(int i) {
    POINT2D tempPoint = { (particleCount - 1 - i) % windowWidth, i / windowWidth };
    if (ColorCompare(ColorAtPoint(tempPoint), _MaterialSand)) {
        MaterialLogicSand(tempPoint);
    }
    else if (ColorCompare(ColorAtPoint(tempPoint), _MaterialWater)) {
        MaterialLogicWater(tempPoint);
    }
    else if (ColorCompare(ColorAtPoint(tempPoint), _MaterialRockParticle)) {
        MaterialLogicRockParticle(tempPoint);
    }
}
void PhysUpdate()
{
    if (frameSide) {
        for (int i = 0; i < particleCount; i++) {
            PhysUpdate1(i);
        }
    }
    else {
        for (int i = 0; i < particleCount; i++) {
            PhysUpdate2(i);
        }
    }
    frameSide = !frameSide;
}
void ParallelPhysUpdate()
{
    if (frameSide) {
        ParallelFor(0, particleCount, 4, PhysUpdate1);
    }
    else {
        ParallelFor(0, particleCount, 4, PhysUpdate2);
    }
    frameSide = !frameSide;
}

// Recolor all pixels to particles, RED and BLUE channels need to be switched because it's 24bit color
void ParticlesToPixelsParallel(int i) {
    *(pixels + 3 * i) = (particles + i)->color.b;
    *(pixels + 3 * i + 1) = (particles + i)->color.g;
    *(pixels + 3 * i + 2) = (particles + i)->color.r;
    //(particles + i)->updated = 0;
}
void ParticlesToPixels() { 
    ParallelFor(0, particleCount, 4, ParticlesToPixelsParallel);
}

// Draws a red cursor circle
POINT2D mouseCoords;
void MouseCircle(MSG message) {
    POINT2D tempPoint = { LOWORD(message.lParam), abs(HIWORD(message.lParam) - windowHeight) };
    if (PointInWindow(tempPoint) && message.message != WM_CHAR) {
        mouseCoords = tempPoint;
    }
    double degreeStep = (360.0 / ((2 * brushSize * M_PI) * 10.0));
    for (double degrees = 0; degrees < 360.0; degrees += degreeStep) {
        POINT2D travelDot = { mouseCoords.x + (brushSize * sin(degrees)), mouseCoords.y + (brushSize * cos(degrees)) };
        if (PointInWindow(travelDot)) {
            int i = travelDot.x + (travelDot.y * windowWidth);
            *(pixels + 3 * i) = _ColorRed.b;
            *(pixels + 3 * i + 1) = _ColorRed.g;
            *(pixels + 3 * i + 2) = _ColorRed.r;
        }
    }
}
