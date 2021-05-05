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
    float x = location.x;
    float y = location.y;
    if (y > 0 && ColorAtPoint((POINT2D){x, y - 1}) != _MaterialSolid && ColorAtPoint((POINT2D){x, y - 1}) != _MaterialSand)
    {
        unsigned int tempMaterial = ColorAtPoint((POINT2D){x, y - 1});
        PixelsDrawPoint((POINT2D){x, y - 1}, _MaterialSand);
        PixelsDrawPoint((POINT2D){x, y}, tempMaterial);
    }
    else if (y > 0 && x > 0 && ColorAtPoint((POINT2D){x - 1, y - 1}) != _MaterialSolid && ColorAtPoint((POINT2D){x - 1, y - 1}) != _MaterialSand)
    {
        unsigned int tempMaterial = ColorAtPoint((POINT2D){x - 1, y - 1});
        PixelsDrawPoint((POINT2D){x - 1, y - 1}, _MaterialSand);
        PixelsDrawPoint((POINT2D){x, y}, tempMaterial);
    }
    else if (y > 0 && x < calcWindowWidth && ColorAtPoint((POINT2D){x + 1, y - 1}) != _MaterialSolid && ColorAtPoint((POINT2D){x + 1, y - 1}) != _MaterialSand)
    {
        unsigned int tempMaterial = ColorAtPoint((POINT2D){x + 1, y - 1});
        PixelsDrawPoint((POINT2D){x + 1, y - 1}, _MaterialSand);
        PixelsDrawPoint((POINT2D){x, y}, tempMaterial);
    }
}

int randDirection = 1;
// Particle logic for water
void MaterialLogicWater(POINT2D location)
{
    float x = location.x;
    float y = location.y;

    if (y > 0 && ColorAtPoint((POINT2D){x, y - 1}) == _backgroundColor)
    {
        PixelsDrawPoint((POINT2D){x, y - 1}, _MaterialWater);
        PixelsDrawPoint((POINT2D){x, y}, _backgroundColor);
    }
    else if (y > 0 && x > 0 && x < calcWindowWidth && ColorAtPoint((POINT2D){x - randDirection, y - 1}) == _backgroundColor)
    {
        PixelsDrawPoint((POINT2D){x - randDirection, y - 1}, _MaterialWater);
        PixelsDrawPoint((POINT2D){x, y}, _backgroundColor);
    }
    else if (y > 0 && x > 0 && x < calcWindowWidth && ColorAtPoint((POINT2D){x + randDirection, y - 1}) == _backgroundColor)
    {
        PixelsDrawPoint((POINT2D){x + randDirection, y - 1}, _MaterialWater);
        PixelsDrawPoint((POINT2D){x, y}, _backgroundColor);
    }
    else if (x > 0 && x < calcWindowWidth && ColorAtPoint((POINT2D){x - randDirection, y}) == _backgroundColor)
    {
        PixelsDrawPoint((POINT2D){x - randDirection, y}, _MaterialWater);
        PixelsDrawPoint((POINT2D){x, y}, _backgroundColor);
    }
    else if (x > 0 && x < calcWindowWidth && ColorAtPoint((POINT2D){x + randDirection, y}) == _backgroundColor)
    {
        PixelsDrawPoint((POINT2D){x + randDirection, y}, _MaterialWater);
        PixelsDrawPoint((POINT2D){x, y}, _backgroundColor);
    }

    randDirection *= -1;
}