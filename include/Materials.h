#include "..\include\MyStructs.h"

#ifndef MATERIALS_H
#define MATERIALS_H

// Particle logic functions
void MaterialLogicSand(POINT2D location);
void MaterialLogicWater(POINT2D location);
void MaterialLogicRockParticles(POINT2D location);

// Particle materials
#define _MaterialRockSolid 0x414042
#define _MaterialRockParticles 0x58595B
#define _MaterialSand 0xEDD9AF
#define _MaterialWater 0x2389DA

#endif