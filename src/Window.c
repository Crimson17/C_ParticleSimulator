#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdint.h>
#include "..\include\MyFunctions.h"
#include "..\include\MyStructs.h"
#include "..\include\GlobalVars.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
    // Win props
    WindowProperties();
    // Setup
    if (_hideConsole)
    {
        FreeConsole();
    }
    srand((unsigned)time(NULL));
    globalRunning = 1;
    float timeToSleep = 0.0;

    // Define window class
    char *CLASS_NAME = "GameWindow";
    WNDCLASS window_class = {0};
    window_class.lpfnWndProc = WindowProc; // Communicates with windows, when yuo click on "X" windows sends a WM_CLOSE message
    window_class.hInstance = hInstance;
    window_class.lpszClassName = CLASS_NAME;
    RegisterClass(&window_class);

    // Create window and specify window properties
    HWND window = CreateWindowEx(0, CLASS_NAME, "My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, _windowWidth, _windowHeight, 0, 0, hInstance, 0);

    // Get window width and height
    RECT rect;
    GetClientRect(window, &rect);
    calcWindowWidth = rect.right - rect.left;
    calcWindowHeight = rect.bottom - rect.top;

    // Allocate memory for the pixels
    _pixelMemoryLen = calcWindowWidth * calcWindowHeight;
    _pixelMemory = VirtualAlloc(0, _pixelMemoryLen * sizeof(unsigned int), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    // Pixel properties
    bitmap_info.bmiHeader.biSize = sizeof(bitmap_info.bmiHeader);
    bitmap_info.bmiHeader.biWidth = calcWindowWidth;   // Window width
    bitmap_info.bmiHeader.biHeight = calcWindowHeight; // Window height
    bitmap_info.bmiHeader.biPlanes = 1;                // Old stuff, has to be 1 now
    bitmap_info.bmiHeader.biBitCount = 32;             // How many bits for each pixel
    bitmap_info.bmiHeader.biCompression = BI_RGB;      // Compression type, RI_RGB = no compression

    // Access window, so it can be rendered to
    HDC hdc = GetDC(window);

    // Inital pixel colors
    PixelsFillSolid(_pixelMemory, _pixelMemoryLen, _ColorWhite);

    // User stuff
    if (MyMain())
    {
        return -1;
    }

    // Calculate time needed to sleep for constant fps
    if (_fps > 0)
    {
        timeToSleep = (1 / _fps) * 1000;
    }

    // Keep window open
    while (globalRunning)
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
        // Gets called every frame update
        FrameUpdate(message);
        // Render bits from the memmory to screen
        StretchDIBits(hdc, 0, 0, calcWindowWidth, calcWindowHeight, 0, 0, calcWindowWidth, calcWindowHeight, _pixelMemory, &bitmap_info, DIB_RGB_COLORS, SRCCOPY);
        Sleep(timeToSleep);
    }

    // Free pixel memory
    free(_pixelMemory);
    return 0;
}