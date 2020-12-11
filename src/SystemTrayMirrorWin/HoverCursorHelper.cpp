#include "HoverCursorHelper.h"

HoverCursorHelper::HoverCursorHelper(HWND hWnd, LPCTSTR cursor)
{
    this->hWnd = hWnd;
    this->cursor = cursor;

    SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)this);
    prevWndProc = (WNDPROC)SetWindowLongPtr(hWnd, GWL_WNDPROC, (LONG_PTR)&WndProc);
}

HoverCursorHelper::~HoverCursorHelper()
{
    if (hWnd != NULL)
    {
        SetWindowLongPtr(hWnd, GWL_WNDPROC, (LONG_PTR)prevWndProc);
    }
}

LRESULT HoverCursorHelper::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    HoverCursorHelper *pThis = (HoverCursorHelper*) GetWindowLongPtr(hWnd, GWL_USERDATA);
    
    switch(message) {
        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_MOUSEHOVER:
            SetCursor(LoadCursor(NULL, pThis->cursor));
            break;
        case WM_NCHITTEST:
            SetCursor(LoadCursor(NULL, pThis->cursor));
            break;
        default:
            break;
    }

    return CallWindowProc(pThis->prevWndProc, hWnd, message, wParam, lParam);
}