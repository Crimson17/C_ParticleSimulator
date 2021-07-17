#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdint.h>
#include "MyStructs.h"
#include "MyFunctions.h"
#include "Materials.h"


int solidMaterialExists = 0;
int counter = 0;
// Gets called ever frame update
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
    else if (message.wParam == 32 && solidMaterialExists) {
        for (int i = 0; i < particleCount; i++) {
            if (ColorCompare((particles + i)->color, _MaterialRockSolid)) {
                (particles + i)->color = _MaterialRockParticle;
            }
        }
        solidMaterialExists = 0;
    }
}


// Updates physics every frame update
void PhysUpdate()
{
    int frameSide = 1;
    // Iterate through the whole window, and check for each color of the pixel, then call appropriate logic function
    if (frameSide) {
        for (int y = 0; y < windowHeight; y++) {
            for (int x = 0; x < windowWidth; x++) {
                POINT2D tempPoint = { x, y };
                if(ColorCompare(ColorAtPoint(tempPoint), _MaterialSand)){
                    MaterialLogicSand(tempPoint);
                }
                else if (ColorCompare(ColorAtPoint(tempPoint), _MaterialWater)) {
                    MaterialLogicWater(tempPoint);
                }
                else if (ColorCompare(ColorAtPoint(tempPoint), _MaterialRockParticle)) {
                    MaterialLogicRockParticle(tempPoint);
                }
            }
        }
        frameSide = 0;
    }
    else {
        for (int y = 0; y < windowHeight; y++) {
            for (int x = windowWidth; x >= 0; x--) {
                POINT2D tempPoint = { x, y };
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
        }
        frameSide = 1;
    }
}