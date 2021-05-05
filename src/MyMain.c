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
    _windowHeight = 900 + 40;
    //  Hides the console
    _hideConsole = 1;
    // If the fps is set to 0 or less there will be no frame limitations
    _fps = 0;
}

// Gets called once before frame rendering has started
int MyMain(void)
{
    PixelsFillSolid(_ColorKrimzoFav);

    POINT2D A = {0, 100};
    POINT2D B = {300, 55};
    POINT2D C = {900, 400};
    PixelsDrawTriangle(A, B, C, _ColorOrange);

    return 0;
}

int frameCounter = 0;
int randColor = 0;
// Gets called ever frame update
void FrameUpdate(MSG message)
{
    if (message.wParam == 1)
    {
        POINT2D mouseCoords = {LOWORD(message.lParam), abs(HIWORD(message.lParam) - _windowHeight) - 40};
        PixelsDrawPoint(mouseCoords, _ColorOrange);
    }
    frameCounter++;
}