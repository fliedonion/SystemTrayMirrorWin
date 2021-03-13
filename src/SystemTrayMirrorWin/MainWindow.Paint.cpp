#include "MainWindow.h"

std::vector<HWND> staticHandles;
std::vector<HBITMAP> deleteReservedBmp;


RECT MainWindow::GetLocation(HWND hWnd) {
    RECT rc;
    if (hWnd == NULL) {
        rc = RECT();
        return rc;
    }
    GetClientRect(hWnd, &rc); // window size (0, 0, w, h)
    MapWindowPoints(hWnd, GetParent(hWnd), (LPPOINT)&rc, 2); // relative location from parent (left, top, left + w, top + h)
    return rc;
}

void MainWindow::DrawStaticToMemoryDC(HDC destDC, HWND hwndStatic) {

    HDC hdcStatic = GetDC(hwndStatic);

    RECT rc = GetLocation(hwndStatic);
    BitBlt(destDC, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
           hdcStatic, 0, 0, SRCCOPY);

    ReleaseDC(hwndStatic, hdcStatic);
}

void MainWindow::DrawTitleBar(HDC hDCOfHWndWantToUpdate, const std::vector<HWND> &staticHandles, HWND closeButton) {
    static COLORREF titleBarColor = RGB(217, 217, 217);

    RECT rcCloseButton = GetLocation(closeButton);

    // CreateCompatibleDC creates a memory DC compatible with the (arg DC's)application's current screen.
    // Compatible but 1x1 monochrome pixel.
    HDC hMemoryDC = CreateCompatibleDC(hDCOfHWndWantToUpdate);

    // Create Same Color Info with hDCOfHWndWantToUpdate and specific size (you want).
    int canvasWidth = rcCloseButton.right + 1;
    HBITMAP hBmpCanvas = CreateCompatibleBitmap(hDCOfHWndWantToUpdate, canvasWidth, CUSTOM_HEADER_HEIGHT);
    SelectObject(hMemoryDC, hBmpCanvas);

    // Draw to MemoryBitmap
    HBRUSH brush = CreateSolidBrush(titleBarColor);
    SelectObject(hMemoryDC, brush);
    Rectangle(hMemoryDC, 0, 0, canvasWidth, CUSTOM_HEADER_HEIGHT);


    for(HWND hwndStatic : staticHandles) {
        DrawStaticToMemoryDC(hMemoryDC, hwndStatic);
    }

    // Copy to Target DC want to update.
    BitBlt(hDCOfHWndWantToUpdate, 0, 0, canvasWidth, CUSTOM_HEADER_HEIGHT,
           hMemoryDC, 0, 0, SRCCOPY);

    DeleteObject(brush);
    DeleteDC(hMemoryDC);
}

void MainWindow::DrawTitleBar(HWND hWndWantToUpdate, const std::vector<HWND> &staticHandles, HWND closeButton) {
    HDC hDCOfHWndWantToUpdate = GetDC(hWndWantToUpdate);
    DrawTitleBar(hDCOfHWndWantToUpdate, staticHandles, closeButton);
    ReleaseDC(hWndWantToUpdate, hDCOfHWndWantToUpdate);
}


void MainWindow::UpdateByTimer() {
    if (hbmp){
        // TODO: only reserve.
        // 更新と描画がかぶる場合とか。
        // DeleteObject(hbmp);
        deleteReservedBmp.push_back(hbmp);
    }
    // HBITMAP hbmp;
    HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONULL);

    MONITORINFOEX mi;
    mi.cbSize = sizeof(MONITORINFOEX);
    LONG monitorWidth = -1;
    LONG monitorHeight = -1;
    if (hMonitor) {
        if (GetMonitorInfo(hMonitor, &mi)) {
            monitorWidth = mi.rcMonitor.right - mi.rcMonitor.left;
            monitorHeight = mi.rcMonitor.bottom - mi.rcMonitor.top;
        }
    }

    SIZEL imagesize, destsize;
    RECT  windowRect;
    hbmp = CaptureNotificationArea(&imagesize);
    GetWindowRect(hWnd, &windowRect);

    if(imagesize.cx < MIN_WIDTH) {
        // apply min-width to close button.
        imagesize.cx = MIN_WIDTH;
    }

    // layout window items
    destsize.cx = imagesize.cx;
    destsize.cy = imagesize.cy;

    if (IsDoubleSize) {
        destsize.cx = (LONG)(destsize.cx * 1.5);
        destsize.cy = (LONG)(destsize.cy * 1.5);
    }

    RECT rc;
    SetRect(&rc,
            0, 0,
            destsize.cx, destsize.cy + CUSTOM_HEADER_HEIGHT);


    // window itself
    if (monitorWidth != -1 && IsFitRBEnabled) {
        if(windowRect.left + (rc.right - rc.left) > monitorWidth) {
            windowRect.left = mi.rcMonitor.right - (rc.right - rc.left);
        }
        if(windowRect.top + (rc.bottom - rc.top) > monitorHeight) {
            windowRect.top = mi.rcMonitor.bottom - (rc.bottom - rc.top);
        }
    }

    // RESIZE MainWindow(not move)
    MoveWindow(hWnd,
               windowRect.left, windowRect.top,
               rc.right - rc.left,
               rc.bottom - rc.top,
               FALSE);

    // static
    //MoveWindow(hWndStatic,
    //    0, 0,
    //    destsize.cx - CLOSE_BUTTON_WIDTH,
    //    CUSTOM_HEADER_HEIGHT ,
    //    FALSE);


    // close button
    MoveWindow(hWndCloseButton,
               destsize.cx - CLOSE_BUTTON_WIDTH, 0,
               CLOSE_BUTTON_WIDTH,
               CUSTOM_HEADER_HEIGHT,
               FALSE);

    SetWindowPos(hWndCloseButton, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOCOPYBITS | SWP_NOREDRAW);

    InvalidateRect(hWnd, NULL, 0);
}

// WM_PAINT
void MainWindow::OnPaint(HWND hWnd, HDC hdc) {
    HDC hMdc;

    SIZEL imagesize, destsize;

    {
        RECT  windowRect;
        GetWindowRect(hWnd, &windowRect);
        destsize.cx = windowRect.right - windowRect.left;
        destsize.cy = windowRect.bottom - windowRect.top - CUSTOM_HEADER_HEIGHT;
    }

    {
        BITMAP bm;
        GetObject(hbmp, sizeof(BITMAP), &bm);
        imagesize.cx = bm.bmWidth;
        imagesize.cy = bm.bmHeight;
    }



    if (!hbmp) {
        // fill background
        RECT bodyRect;
        SetRect(&bodyRect, 0, CUSTOM_HEADER_HEIGHT, destsize.cx, destsize.cy + CUSTOM_HEADER_HEIGHT);

    } else {
        hMdc = CreateCompatibleDC(hdc);
        SelectObject(hMdc, hbmp);
        if (!IsDoubleSize) {
            BitBlt(hdc, 0, CUSTOM_HEADER_HEIGHT, destsize.cx, destsize.cy, hMdc, 0, 0, SRCCOPY);
        }
        else {
            int oldBltMode = SetStretchBltMode(hdc, HALFTONE);

            StretchBlt(hdc, 0,
                       CUSTOM_HEADER_HEIGHT, destsize.cx, destsize.cy,
                       hMdc, 0, 0, imagesize.cx, imagesize.cy,
                       SRCCOPY);

            if (oldBltMode != 0) {
                SetStretchBltMode(hdc, oldBltMode);
            }
        }

        DeleteDC(hMdc);
        // DeleteObject(hbmp);
    }

    for(HBITMAP hbmp4del: deleteReservedBmp) {
        DeleteObject(hbmp4del);
    }

    DrawTitleBar(hdc, staticHandles, hWndCloseButton);
}

