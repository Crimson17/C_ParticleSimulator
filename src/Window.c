#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdint.h>
#include "..\include\Functions.h"
#include "..\include\Structures.h"
#include "..\include\GVariables.h"
#include "..\include\Updates.h"

// Functions needed for window creation
LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
    // Setup
    WindowProperties();
    if (_hideConsole)
    {
        FreeConsole();
    }
    srand((unsigned)time(NULL));
    _globalRunning = 1;

    // Define window class
    char *CLASS_NAME = "GameWindow";
    WNDCLASS window_class = {0};
    window_class.lpfnWndProc = WindowProc; // Communicates with windows, when yuo click on "X" windows sends a WM_CLOSE message
    window_class.hInstance = hInstance;
    window_class.lpszClassName = CLASS_NAME;
    RegisterClass(&window_class);

    // Create window and specify window properties
    HWND window = CreateWindowEx(0, CLASS_NAME, 0, 0, (ScreenX - _windowWidth) / 2, (ScreenY - _windowHeight) / 2, _windowWidth, _windowHeight, 0, 0, hInstance, 0);

    // Remove window title bar
    SetWindowLong(window, GWL_STYLE, 0);
    ShowWindow(window, SW_SHOW);

    // Allocate memory
    _memoryLen = _windowWidth * _windowHeight;
    _pixels = (unsigned int*)calloc(_memoryLen, sizeof(unsigned int));
    if(_pixels == NULL){
        return -1;
    }
    _particles = (PARTICLE *)calloc(_memoryLen, sizeof(PARTICLE));
    if(_particles == NULL){
        return -1;
    }

    // Pixel properties
    _bitmap_info.bmiHeader.biSize = sizeof(_bitmap_info.bmiHeader);
    _bitmap_info.bmiHeader.biWidth = _windowWidth;   // Window width
    _bitmap_info.bmiHeader.biHeight = _windowHeight; // Window height
    _bitmap_info.bmiHeader.biPlanes = 1;                // Old stuff, has to be 1 now
    _bitmap_info.bmiHeader.biBitCount = 32;             // How many bits for each pixel
    _bitmap_info.bmiHeader.biCompression = BI_RGB;      // Compression type, RI_RGB = no compression

    // Access window, so it can be rendered to
    HDC hdc = GetDC(window);

    // Inital pixel colors
    PixelsFillSolid(_backgroundColor);

    // Keep window open
    while (_globalRunning)
    {
        // Message = Pressed Keys (Something like a key listener)
        MSG message;
        while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
        {
            // Translate key code to real char
            TranslateMessage(&message);
            // Send message to MSG message
            DispatchMessage(&message);
        }
        // Handle the input
        Input(message);
        // Update the particle physics
        PhysUpdate();
        // Write particles to pixel memory 
        //ParticlesToPixels();
        // Render bits from the memmory to screen
        StretchDIBits(hdc, 0, 0, _windowWidth, _windowHeight, 0, 0, _windowWidth, _windowHeight, _pixels, &_bitmap_info, DIB_RGB_COLORS, SRCCOPY);
    }

    // Free memory
    free(_pixels);
    free(_particles);
    return 0;
}

// Communicates with windows
LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result;
    switch (message)
    {
    case WM_CHAR:
        if(wParam == 27){
            _globalRunning = 0;
        }
        break;
    default:
        result = DefWindowProc(window, message, wParam, lParam);
        break;
    }
    return result;
}
