#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdint.h>
#include "..\include\MyFunctions.h"
#include "..\include\MyStructs.h"
#include "..\include\GlobalVars.h"

// Window properties duh
void WindowProperties()
{
    // Screen size
    _windowWidth = 1800;
    _windowHeight = 900 + 30;
    //  Hides the console
    _hideConsole = 1;
    // If the fps is set to 0 or less there will be no frame limitations
    _fps = 120;
}

// Gets called once before frame rendering has started
int MyMain(void)
{
    PixelsFillSolid(_pixelMemory, _pixelMemoryLen, _ColorKrimzoFav);

    POINT2D A = {0, 100};
    POINT2D B = {300, 55};
    POINT2D C = {900, 400};
    PixelsDrawTriangle(_pixelMemory, A, B, C, _ColorOrange);

    return 0;
}

int frameCounter = 0;
int randColor = 0;
// Gets called ever frame update
void FrameUpdate(MSG message)
{
    if (frameCounter % 10 == 0)
    {
        randColor = 0 + (float)rand() / RAND_MAX * (0xFFFFFF + 1);
    }
    PixelsDrawCircle(_pixelMemory, (POINT2D){frameCounter, 500}, (POINT2D){frameCounter, 600}, randColor);
    frameCounter++;
}