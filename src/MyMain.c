#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdint.h>
#include "..\include\MyFunctions.h"
#include "..\include\MyStructs.h"
#include "..\include\GlobalVars.h"
#include "..\include\Materials.h"

// Window properties duh
void WindowProperties()
{
    // Screen size
    _windowWidth = 1800;
    _windowHeight = 900;
    // Default background color
    _backgroundColor = _ColorKrimzoFav;
    // If the fps is set to 0 or less there will be no frame limitations
    _fps = 0;
    // Hides the console
    _hideConsole = 1;
    // Size of the drawing brush
    _brushSize = 10;
    // Enable/Disable particle physics
    _particlePhysics = 1;
}

// Gets called once before frame rendering has started
int MyMain(void)
{
    return 0;
}

int solidMaterialExists = 0;
// Gets called ever frame update
void FrameUpdate(MSG message)
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
        for (int i = 0; i < _pixelMemoryLen; i++)
        {
            if (*(_pixelMemory + i) == _MaterialRockSolid)
            {
                *(_pixelMemory + i) = _MaterialRockParticles;
            }
        }
        solidMaterialExists = 0;
    }
}

int frameSide = 1;
// Updates physics every frame update
void PhysUpdate()
{
    if (_particlePhysics)
    {
        // Iterate through the whole window, and check for each color of the pixel, then call appropriate logic function
        POINT2D tempPoint = {0};
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
}