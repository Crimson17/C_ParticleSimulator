#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "..\include\MyFunctions.h"
#include "..\include\MyStructs.h"
#include "..\include\GlobalVars.h"
#include "..\include\Materials.h"

// Particle logic for sand
void MaterialLogicSand(POINT2D location)
{
    int x = location.x;
    int y = location.y;

    // First, check one down
    if (location.y > 0 && ColorAtPoint((POINT2D){x, y - 1}) != _MaterialSolid && ColorAtPoint((POINT2D){x, y - 1}) != _MaterialSand)
    {
        unsigned int tempMaterial = ColorAtPoint((POINT2D){x, y - 1});
        PixelsDrawPoint((POINT2D){x, y - 1}, _MaterialSand);
        PixelsDrawPoint((POINT2D){x, y}, tempMaterial);
    }
    // Then
    // The bottom-right
    else if (location.y > 0 && location.x < _windowWidth - 1 && ColorAtPoint((POINT2D){x + 1, y - 1}) != _MaterialSolid && ColorAtPoint((POINT2D){x + 1, y - 1}) != _MaterialSand)
    {
        unsigned int tempMaterial = ColorAtPoint((POINT2D){x + 1, y - 1});
        PixelsDrawPoint((POINT2D){x + 1, y - 1}, _MaterialSand);
        PixelsDrawPoint((POINT2D){x, y}, tempMaterial);
    }
    // The bottom-left
    else if (location.y > 0 && location.x > 0 && ColorAtPoint((POINT2D){x - 1, y - 1}) != _MaterialSolid && ColorAtPoint((POINT2D){x - 1, y - 1}) != _MaterialSand)
    {
        unsigned int tempMaterial = ColorAtPoint((POINT2D){x - 1, y - 1});
        PixelsDrawPoint((POINT2D){x - 1, y - 1}, _MaterialSand);
        PixelsDrawPoint((POINT2D){x, y}, tempMaterial);
    }
}

// Particle logic for water
void MaterialLogicWater(POINT2D location)
{
    float x = location.x;
    float y = location.y;

    // First, check one down
    if (location.y > 0 && ColorAtPoint((POINT2D){x, y - 1}) == _backgroundColor)
    {
        PixelsDrawPoint((POINT2D){x, y - 1}, _MaterialWater);
        PixelsDrawPoint(location, _backgroundColor);
    }
    // Then
    // The bottom-right
    else if (location.y > 0 && location.x < _windowWidth - 1 && ColorAtPoint((POINT2D){x + 1, y - 1}) == _backgroundColor)
    {
        PixelsDrawPoint((POINT2D){x + 1, y - 1}, _MaterialWater);
        PixelsDrawPoint(location, _backgroundColor);
    }
    // The bottom-left
    else if (location.y > 0 && location.x > 0 && ColorAtPoint((POINT2D){x - 1, y - 1}) == _backgroundColor)
    {
        PixelsDrawPoint((POINT2D){x - 1, y - 1}, _MaterialWater);
        PixelsDrawPoint(location, _backgroundColor);
    }
    // The right
    else if (location.x < _windowWidth - 1 && ColorAtPoint((POINT2D){x + 1, y}) == _backgroundColor)
    {
        PixelsDrawPoint((POINT2D){x + 1, y}, _MaterialWater);
        PixelsDrawPoint(location, _backgroundColor);
    }
    // The left
    else if (location.x > 0 && ColorAtPoint((POINT2D){x - 1, y}) == _backgroundColor)
    {
        PixelsDrawPoint((POINT2D){x - 1, y}, _MaterialWater);
        PixelsDrawPoint(location, _backgroundColor);
    }
}

// Still WIP
// Particle logic for purple exploded
void MaterialLogicSolidExploded(POINT2D location)
{
    float x = location.x;
    float y = location.y;
    // First, check one up
    if (location.y < _windowHeight - 1 && ColorAtPoint((POINT2D){x, y + 1}) != _MaterialSolidExploded)
    {
        unsigned int tempMaterial = ColorAtPoint((POINT2D){x, y + 1});
        PixelsDrawPoint((POINT2D){x, y + 1}, _MaterialSolidExploded);
        PixelsDrawPoint(location, tempMaterial);
    }
    // Then
    // The top-right
    else if (location.y < _windowHeight - 1 && location.x < _windowWidth - 1 && ColorAtPoint((POINT2D){x + 1, y + 1}) == _backgroundColor)
    {
        PixelsDrawPoint((POINT2D){x + 1, y + 1}, _MaterialSolidExploded);
        PixelsDrawPoint(location, _backgroundColor);
    }
    // The top-left
    else if (location.y < _windowHeight - 1 && location.x > 0 && ColorAtPoint((POINT2D){x - 1, y + 1}) == _backgroundColor)
    {
        PixelsDrawPoint((POINT2D){x - 1, y + 1}, _MaterialSolidExploded);
        PixelsDrawPoint(location, _backgroundColor);
    }
    // The right
    else if (location.x < _windowWidth - 1 && ColorAtPoint((POINT2D){x + 1, y}) == _backgroundColor)
    {
        PixelsDrawPoint((POINT2D){x + 1, y}, _MaterialSolidExploded);
        PixelsDrawPoint(location, _backgroundColor);
    }
    // The left
    else if (location.x > 0 && ColorAtPoint((POINT2D){x - 1, y}) == _backgroundColor)
    {
        PixelsDrawPoint((POINT2D){x - 1, y}, _MaterialSolidExploded);
        PixelsDrawPoint(location, _backgroundColor);
    }
}