#pragma once
#include <windows.h>

class HoverCursorHelper
{
public:
    HWND hWnd;
    LPCTSTR cursor;
    WNDPROC prevWndProc;
    HoverCursorHelper(HWND, LPCTSTR);
    ~HoverCursorHelper();
private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

