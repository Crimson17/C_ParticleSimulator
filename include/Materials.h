#include "..\include\MyStructs.h"

#ifndef MATERIALS_H
#define MATERIALS_H

void MaterialLogicSand(POINT2D location);
void MaterialLogicWater(POINT2D location);

#endif

// Particle materials
#define _MaterialSolid 0x8806CE
#define _MaterialSand 0xEDD9AF
#define _MaterialWater 0x2389DA