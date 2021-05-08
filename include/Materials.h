#include "..\include\Structures.h"

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

// Color macros
#define _ColorBlack 0x000000
#define _ColorWhite 0xFFFFFF
#define _ColorRed 0xFF0000
#define _ColorRedDark 0x770000
#define _ColorGreen 0x00FF00
#define _ColorGreenDark 0x007700
#define _ColorBlue 0x0000FF
#define _ColorBlueDark 0x000077
#define _ColorYellow 0xFFEE00
#define _ColorOrange 0xFF9900
#define _ColorCyan 0x00CC99
#define _ColorMagenta 0xFF00FF
#define _ColorBrown 0x804000
#define _ColorGray 0x7D7D7D
#define _ColorKrimzoFav 0x112233

#endif