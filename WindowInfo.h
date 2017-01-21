#ifndef WINDOWINFO_H
#define WINDOWINFO_H

#include <windows.h>

struct WindowInfo
{
    WindowInfo(HWND hwnd, int screenWidth, int screenHeight)
        : m_hwnd(hwnd), m_screenWidth(screenWidth), m_screenHeight(screenHeight)
    {}

    HWND m_hwnd;
    int m_screenWidth;
    int m_screenHeight;
};

#endif // WINDOWINFO_H
