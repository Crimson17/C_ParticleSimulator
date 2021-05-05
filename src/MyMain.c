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
    // Default background color
    _backgroundColor = _ColorKrimzoFav;
    // If the fps is set to 0 or less there will be no frame limitations
    _fps = 0;
    //  Hides the console
    _hideConsole = 1;
}

// Gets called once before frame rendering has started
int MyMain(void)
{
    PixelsDrawRectangle((POINT2D){300, 100}, (POINT2D){600, 250}, _MaterialSolid);

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
        PixelsBrush(mouseCoords, _MaterialSand);
    }
    if (message.wParam == 2)
    {
        POINT2D mouseCoords = {LOWORD(message.lParam), abs(HIWORD(message.lParam) - _windowHeight) - 40};
        PixelsBrush(mouseCoords, _MaterialSolid);
    }
    frameCounter++;
}

// Updates physics every frame update
void PhysUpdate(){
    for (int y = 0; y < calcWindowHeight; y++)
    {
        for (int x = 0; x < calcWindowWidth; x++)
        {
            switch (ColorAtPoint((POINT2D){x, y}))
            {
            case _MaterialSand:
                if(y > 0 && ColorAtPoint((POINT2D){x, y-1}) == _backgroundColor){
                    PixelsDrawPoint((POINT2D){x, y-1}, _MaterialSand);
                    PixelsDrawPoint((POINT2D){x, y}, _backgroundColor);
                }
                else if(y > 0 && x > 0 && ColorAtPoint((POINT2D){x-1, y-1}) == _backgroundColor){
                    PixelsDrawPoint((POINT2D){x-1, y-1}, _MaterialSand);
                    PixelsDrawPoint((POINT2D){x, y}, _backgroundColor);
                }
                else if(y > 0 && x < calcWindowWidth && ColorAtPoint((POINT2D){x+1, y-1}) == _backgroundColor){
                    PixelsDrawPoint((POINT2D){x+1, y-1}, _MaterialSand);
                    PixelsDrawPoint((POINT2D){x, y}, _backgroundColor);
                }
                break;
            
            default:
                break;
            }
        }
    }
}