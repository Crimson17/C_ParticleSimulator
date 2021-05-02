#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdint.h>
#include "..\include\MyFunctions.h"
#include "..\include\MyStructs.h"

int globalRunning = 1;
int width = 0;
int height = 0;

void *memory;
BITMAPINFO bitmap_info;

LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result;
    switch (message)
    {
    case WM_CLOSE:
        globalRunning = 0;
        break;

    default:
        result = DefWindowProc(window, message, wParam, lParam);
        break;
    }
    return result;
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
    // Define window class
    char CLASS_NAME[] = "GameWindow";
    WNDCLASS window_class = {0};
    window_class.lpfnWndProc = WindowProc;
    window_class.hInstance = hInstance;
    window_class.lpszClassName = CLASS_NAME;
    RegisterClass(&window_class);

    // Create window and specify window properties
    HWND window = CreateWindowEx(0, CLASS_NAME, "My Game", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hInstance, 0);

    // Get window width and height
    RECT rect;
    GetClientRect(window, &rect);
    width = rect.right - rect.left;
    height = rect.bottom - rect.top;

    // Allocate memory for the pixels
    memory = VirtualAlloc(0, width * height * sizeof(unsigned int), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    // Pixel properties
    bitmap_info.bmiHeader.biSize = sizeof(bitmap_info.bmiHeader);
    bitmap_info.bmiHeader.biWidth = width;        // Window width
    bitmap_info.bmiHeader.biHeight = height;      // Window height
    bitmap_info.bmiHeader.biPlanes = 1;           // Old stuff, has to be 1 now
    bitmap_info.bmiHeader.biBitCount = 32;        // How many bits for each pixel
    bitmap_info.bmiHeader.biCompression = BI_RGB; // Compression type, RI_RGB = no compression

    // Access window, so it can be rendered to
    HDC hdc = GetDC(window);

    // Keep window open
    while (globalRunning)
    {
        // Message = Pressed Keys (Something like a key listener)
        MSG message;
        while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
        {
            // Translate key code to real char
            TranslateMessage(&message);
            DispatchMessage(&message);
            printf("Key: %c\n", message);
        }
        // Render bits from the memmory to screen
        StretchDIBits(hdc, 0, 0, width, height, 0, 0, width, height, memory, &bitmap_info, DIB_RGB_COLORS, SRCCOPY);
    }

    // Free pixel memory
    free(memory);
    return 0;
}