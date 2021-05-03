#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdint.h>
#include "..\include\MyFunctions.h"
#include "..\include\MyStructs.h"
#include "..\include\GlobalVars.h"

int MyMain(void){
    PixelsFillSolid(_pixelMemory, _pixelMemoryLen, _ColorKrimzoFav);

    POINT2D A = {0, 100};
    POINT2D B = {300, 55};
    POINT2D C = {900, 500};

    PixelsDrawTriangle(_pixelMemory, A, B, C, _ColorOrange);

    return 0;
}