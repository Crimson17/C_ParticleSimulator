#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <windows.h>
#include <stdint.h>
#include "MyFunctions.h"
#include "MyStructs.h"


// Screen size
int windowWidth = 400;
int windowHeight = 400;
// Default background color
COLOR backgroundColor = { 11, 22, 33 };
// Hides the console
int hideConsole = 1;
// Size of the drawing brush
int brushSize = 10;
// For game loop
int globalRunning = 1;

int particleCount;
BYTE* pixels;
PARTICLE* particles;
BITMAPINFO bitmap_info;

// Functions needed for window creation
LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
    // Setup
    if (hideConsole) {
        FreeConsole();
    }
    srand((unsigned)time(NULL));

    // Define window class
    char* windowName = "Sand Simulation";
    WNDCLASS window_class = { 0 };
    window_class.lpfnWndProc = WindowProc; // Communicates with windows, when you click on "X" windows sends a WM_CLOSE message
    window_class.hInstance = hInstance;
    window_class.lpszClassName = windowName;
    RegisterClass(&window_class);

    // Create window and specify window properties
    HWND window = CreateWindowEx(0, windowName, 0, 0, (ScreenX - windowWidth) / 2, (ScreenY - windowHeight) / 2, windowWidth, windowHeight, 0, 0, hInstance, 0);

    // Remove window title bar
    SetWindowLong(window, GWL_STYLE, 0);
    ShowWindow(window, SW_SHOW);

    // Allocate memory
    particleCount = windowWidth * windowHeight;
    pixels = (BYTE*)calloc(particleCount * 3, sizeof(BYTE));
    if (pixels == NULL) {
        return -1;
    }
    particles = (PARTICLE*)calloc(particleCount, sizeof(PARTICLE));
    if (particles == NULL) {
        return -1;
    }

    // Pixel properties
    bitmap_info.bmiHeader.biSize = sizeof(bitmap_info.bmiHeader);
    bitmap_info.bmiHeader.biWidth = windowWidth;        // Window width
    bitmap_info.bmiHeader.biHeight = windowHeight;      // Window height
    bitmap_info.bmiHeader.biPlanes = 1;                 // Old stuff, has to be 1 now
    bitmap_info.bmiHeader.biBitCount = 24;              // How many bits for each pixel
    bitmap_info.bmiHeader.biCompression = BI_RGB;       // Compression type, RI_RGB = no compression

    // Access window, so it can be rendered to
    HDC hdc = GetDC(window);

    // Inital pixel colors
    FillSolid(backgroundColor);

    // Keep window open
    MSG message;
    while (globalRunning) {
        // Message = Pressed Keys (Something like a key listener)
        while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {
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
        ParticlesToPixels();
        // Render bits from the memmory to screen
        StretchDIBits(hdc, 0, 0, windowWidth, windowHeight, 0, 0, windowWidth, windowHeight, pixels, &bitmap_info, DIB_RGB_COLORS, SRCCOPY);
    }

    // Free memory
    free(pixels);
    free(particles);
    return 0;
}

// Communicates with windows
LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result;
    switch (message) {
    case WM_CHAR:
        if (wParam == 27) {
            globalRunning = 0;
        }
        break;
    case WM_CLOSE:
        globalRunning = 0;
        break;
    default:
        result = DefWindowProc(window, message, wParam, lParam);
        break;
    }
    return result;
}
