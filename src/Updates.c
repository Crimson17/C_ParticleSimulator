#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdint.h>
#include "..\include\Updates.h"
#include "..\include\Structures.h"
#include "..\include\Functions.h"
#include "..\include\GVariables.h"
#include "..\include\Materials.h"

// Window properties duh
void WindowProperties()
{
    // Screen size
    _windowWidth = ScreenX - 100;
    _windowHeight = _windowWidth / 2;
    // Default background color
    _backgroundColor = _ColorKrimzoFav;
    // Hides the console
    _hideConsole = 1;
    // Size of the drawing brush
    _brushSize = 10;
}

int solidMaterialExists = 0;
// Gets called ever frame update
void Input(MSG message)
{
    // Check for left mouse button
    if (message.wParam == 1)
    {
        POINT2D mouseCoords = {LOWORD(message.lParam), abs(HIWORD(message.lParam) - _windowHeight)};
        PixelsBrush(mouseCoords, _brushSize, _MaterialSand);
    }
    // Check for right mouse button
    else if (message.wParam == 2)
    {
        POINT2D mouseCoords = {LOWORD(message.lParam), abs(HIWORD(message.lParam) - _windowHeight)};
        PixelsBrush(mouseCoords, _brushSize, _MaterialWater);
    }
    // Check for middle mouse button
    else if (message.wParam == 16)
    {
        POINT2D mouseCoords = {LOWORD(message.lParam), abs(HIWORD(message.lParam) - _windowHeight)};
        PixelsBrush(mouseCoords, _brushSize, _MaterialRockSolid);
        solidMaterialExists = 1;
    }
    // Check for spacebar
    else if (message.wParam == 32 && solidMaterialExists)
    {
        for (int i = 0; i < _memoryLen; i++)
        {
            if (*(_pixels + i) == _MaterialRockSolid)
            {
                *(_pixels + i) = _MaterialRockParticles;
            }
        }
        solidMaterialExists = 0;
    }
}

int frameSide = 1;
POINT2D tempPoint = {0};
// Updates physics every frame update
void PhysUpdate()
{
    // Iterate through the whole window, and check for each color of the pixel, then call appropriate logic function
    if (frameSide)
    {
        for (int y = 0; y < _windowHeight; y++)
        {
            for (int x = 0; x < _windowWidth; x++)
            {
                tempPoint.x = x;
                tempPoint.y = y;
                switch (ColorAtPoint(tempPoint))
                {
                case _MaterialSand:
                    MaterialLogicSand(tempPoint);
                    break;
                case _MaterialWater:
                    MaterialLogicWater(tempPoint);
                    break;
                case _MaterialRockParticles:
                    MaterialLogicRockParticles(tempPoint);
                    break;
                default:
                    break;
                }
            }
        }
        frameSide = 0;
    }
    else
    {
        for (int y = 0; y < _windowHeight; y++)
        {
            for (int x = _windowWidth; x >= 0; x--)
            {
                tempPoint.x = x;
                tempPoint.y = y;
                switch (ColorAtPoint(tempPoint))
                {
                case _MaterialSand:
                    MaterialLogicSand(tempPoint);
                    break;
                case _MaterialWater:
                    MaterialLogicWater(tempPoint);
                    break;
                case _MaterialRockParticles:
                    MaterialLogicRockParticles(tempPoint);
                    break;
                default:
                    break;
                }
            }
        }
        frameSide = 1;
    }
}