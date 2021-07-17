#ifndef MATERIALS_H
#define MATERIALS_H

#include "MyStructs.h"

// Particle logic functions
void MaterialLogicSand(POINT2D location);
void MaterialLogicWater(POINT2D location);
void MaterialLogicRockParticle(POINT2D location);

// Particle materials
#define _MaterialRockSolid (COLOR){41, 40, 42}
#define _MaterialRockParticle (COLOR){58, 59, 91}
#define _MaterialSand (COLOR){237, 217, 175}
#define _MaterialWater (COLOR){23, 89, 218}

// Color macros
#define _ColorBlack (COLOR){0, 0, 0}
#define _ColorWhite (COLOR){255,255,255}
#define _ColorRed (COLOR){255, 0, 0}
#define _ColorRedDark (COLOR){77, 0, 0}
#define _ColorGreen (COLOR){0, 255, 0}
#define _ColorGreenDark (COLOR){0, 77, 0}
#define _ColorBlue (COLOR){0, 0, 255}
#define _ColorBlueDark (COLOR){0, 0, 77}
#define _ColorYellow (COLOR){255, 238, 0}
#define _ColorOrange (COLOR){255, 153, 0}
#define _ColorCyan (COLOR){0, 204, 153}
#define _ColorMagenta (COLOR){255, 0, 255}
#define _ColorBrown (COLOR){128, 64, 0}
#define _ColorGray (COLOR){125, 125, 125}
#define _ColorKrimzoFav (COLOR){11,22,33}

#endif