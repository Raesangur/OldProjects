#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "user32.lib")

void main()
{
    int aElements[2] ={COLOR_WINDOW,COLOR_ACTIVECAPTION};
    DWORD aOldColors[2];
    DWORD aNewColors[2];

    // Define new colors for the elements
    aNewColors[0] = RGB(0xFF, 0xFF, 0xFF);  // light gray 
    aNewColors[1] = RGB(0x80,0x00,0x80);  // dark purple

    SetSysColors(2,aElements,aNewColors);
}