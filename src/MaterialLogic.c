#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "MyFunctions.h"
#include "MyStructs.h"
#include "Materials.h"

// Particle logic for sand
void MaterialLogicSand(POINT2D location)
{
    int x = location.x;
    int y = location.y;

    // First, check one down
    if (location.y > 0 && (ColorCompare(ColorAtPoint((POINT2D) { x, y - 1 }), backgroundColor) || ColorCompare(ColorAtPoint((POINT2D) { x, y - 1 }), _MaterialWater))) {
        COLOR tempMaterial = ColorAtPoint((POINT2D) { x, y - 1 });
        DrawPoint((POINT2D) { x, y - 1 }, _MaterialSand);
        DrawPoint((POINT2D) { x, y }, tempMaterial);
    }
    // The bottom-right
    else if (y > 0 && x < windowWidth - 1 && (ColorCompare(ColorAtPoint((POINT2D) { x + 1, y - 1 }), backgroundColor) || ColorCompare(ColorAtPoint((POINT2D) { x + 1, y - 1 }), _MaterialWater))) {
        COLOR tempMaterial = ColorAtPoint((POINT2D) { x + 1, y - 1 });
        DrawPoint((POINT2D) { x + 1, y - 1 }, _MaterialSand);
        DrawPoint((POINT2D) { x, y }, tempMaterial);
    }
    // The bottom-left
    else if (y > 0 && x > 0 && (ColorCompare(ColorAtPoint((POINT2D) { x - 1, y - 1 }), backgroundColor) || ColorCompare(ColorAtPoint((POINT2D) { x - 1, y - 1 }), _MaterialWater))) {
        COLOR tempMaterial = ColorAtPoint((POINT2D) { x - 1, y - 1 });
        DrawPoint((POINT2D) { x - 1, y - 1 }, _MaterialSand);
        DrawPoint((POINT2D) { x, y }, tempMaterial);
    }
}

// Particle logic for water
void MaterialLogicWater(POINT2D location)
{
    float x = location.x;
    float y = location.y;

    // First, check one down
    if (y > 0 && ColorCompare(ColorAtPoint((POINT2D) { x, y - 1 }), backgroundColor)) {
        DrawPoint((POINT2D) { x, y - 1 }, _MaterialWater);
        DrawPoint(location, backgroundColor);
    }
    // The bottom-right
    else if (y > 0 && x < windowWidth - 1 && ColorCompare(ColorAtPoint((POINT2D) { x + 1, y - 1 }), backgroundColor)) {
        DrawPoint((POINT2D) { x + 1, y - 1 }, _MaterialWater);
        DrawPoint(location, backgroundColor);
    }
    // The bottom-left
    else if (y > 0 && x > 0 && ColorCompare(ColorAtPoint((POINT2D) { x - 1, y - 1 }), backgroundColor)) {
        DrawPoint((POINT2D) { x - 1, y - 1 }, _MaterialWater);
        DrawPoint(location, backgroundColor);
    }
    // The right
    else if (x < windowWidth - 1 && ColorCompare(ColorAtPoint((POINT2D) { x + 1, y }), backgroundColor)) {
        DrawPoint((POINT2D) { x + 1, y }, _MaterialWater);
        DrawPoint(location, backgroundColor);
    }
    // The left
    else if (x > 0 && ColorCompare(ColorAtPoint((POINT2D) { x - 1, y }), backgroundColor)) {
        DrawPoint((POINT2D) { x - 1, y }, _MaterialWater);
        DrawPoint(location, backgroundColor);
    }
}

// Particle logic for rock
void MaterialLogicRockParticle(POINT2D location)
{
    int x = location.x;
    int y = location.y;

    // First, check one down
    if (y > 0 && (ColorCompare(ColorAtPoint((POINT2D) { x, y - 1 }), backgroundColor) || ColorCompare(ColorAtPoint((POINT2D) { x, y - 1 }), _MaterialWater) || ColorCompare(ColorAtPoint((POINT2D) { x, y - 1 }), _MaterialSand))) {
        COLOR tempMaterial = ColorAtPoint((POINT2D) { x, y - 1 });
        DrawPoint((POINT2D) { x, y - 1 }, _MaterialRockParticle);
        DrawPoint((POINT2D) { x, y }, tempMaterial);
    }
    // The bottom-right
    else if (y > 0 && x < windowWidth - 1 && (ColorCompare(ColorAtPoint((POINT2D) { x + 1, y - 1 }), backgroundColor) || ColorCompare(ColorAtPoint((POINT2D) { x + 1, y - 1 }), _MaterialWater) || ColorCompare(ColorAtPoint((POINT2D) { x + 1, y - 1 }), _MaterialSand))) {
        COLOR tempMaterial = ColorAtPoint((POINT2D) { x + 1, y - 1 });
        DrawPoint((POINT2D) { x + 1, y - 1 }, _MaterialRockParticle);
        DrawPoint((POINT2D) { x, y }, tempMaterial);
    }
    // The bottom-left
    else if (y > 0 && x > 0 && (ColorCompare(ColorAtPoint((POINT2D) { x - 1, y - 1 }), backgroundColor) || ColorCompare(ColorAtPoint((POINT2D) { x - 1, y - 1 }), _MaterialWater) || ColorCompare(ColorAtPoint((POINT2D) { x - 1, y - 1 }), _MaterialSand))) {
        COLOR tempMaterial = ColorAtPoint((POINT2D) { x - 1, y - 1 });
        DrawPoint((POINT2D) { x - 1, y - 1 }, _MaterialRockParticle);
        DrawPoint((POINT2D) { x, y }, tempMaterial);
    }
}