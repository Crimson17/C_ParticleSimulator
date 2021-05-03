#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdint.h>
#include "..\include\MyFunctions.h"
#include "..\include\MyStructs.h"
#include "..\include\GlobalVars.h"


// Gets called once before frame rendering has started
int MyMain(void)
{
    _fps = 30;
    
    PixelsFillSolid(_pixelMemory, _pixelMemoryLen, _ColorKrimzoFav);

    /*
    POINT2D A = {0, 100};
    POINT2D B = {300, 55};
    POINT2D C = {900, 500};

    PixelsDrawTriangle(_pixelMemory, A, B, C, _ColorOrange);
    */
    return 0;
}

int frameCounter = 0;
int frameCounter2 = 0;

// Gets called ever frame update
void FrameUpdate(MSG message)
{
    if(frameCounter < windowWidth){
        PixelsDrawLine(_pixelMemory, (POINT2D){frameCounter, 0}, (POINT2D){frameCounter, windowHeight}, 0 + (float)rand() / RAND_MAX * (0xFFFFFF));
        frameCounter += 2;
    }
    if(frameCounter2 < windowHeight){
        PixelsDrawLine(_pixelMemory, (POINT2D){0, frameCounter2}, (POINT2D){windowWidth, frameCounter2}, 0 + (float)rand() / RAND_MAX * (0xFFFFFF));
        frameCounter2 += 2;
    }
}