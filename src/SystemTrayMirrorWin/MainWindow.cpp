#include "MainWindow.h"


MainWindow::MainWindow()
{
}


MainWindow::~MainWindow()
{
    if (pHHZoom) delete pHHZoom;
    if (pHHTopMost) delete pHHTopMost;
    if (pHHCloseLock) delete pHHCloseLock;
    if (pHHFitRightBottom) delete pHHFitRightBottom;

    KillTimer(hWnd, ID_TIMER);
    if (hFontOptStatic) DeleteObject(hFontOptStatic);
    if (hFontDefault) DeleteObject(hFontDefault);
    if (appBlackBrush) DeleteObject(appBlackBrush);

}

// WM_CREATE
void MainWindow::OnCreate(WPARAM wParam, LPARAM lParam)
{
    appBlackBrush = CreateSolidBrush(RGB(0,0,0));

    LPCREATESTRUCT lpCS = (LPCREATESTRUCT)lParam;

    AddControls(lpCS);
    SetTimer(TimerInterval);
}


void MainWindow::AddControls(LPCREATESTRUCT lpCS){

	hWndStatic = CreateWindowEx( WS_EX_COMPOSITED, 
        _T("STATIC"), _T(""),
		SS_CENTER | WS_CHILD | WS_VISIBLE,
		0, 0, 100, CUSTOM_HEADER_HEIGHT,
		hWnd, 
        (HMENU)IDC_MOVABLE_STATIC,
		lpCS->hInstance, 
        NULL);

    hWndZoomStatic = CreateOptionFeatureStatic(hWnd, lpCS, (HMENU)IDC_STATIC_ZOOM, _T("🔍"), 0);
    pHHZoom = new HoverCursorHelper(hWndZoomStatic, IDC_HAND);

    hWndTopMostStatic = CreateOptionFeatureStatic(hWnd, lpCS, (HMENU)IDC_STATIC_TOPMOST, _T("📌"), 1);
    pHHTopMost = new HoverCursorHelper(hWndTopMostStatic, IDC_HAND);

    hWndCloseLockStatic = CreateOptionFeatureStatic(hWnd, lpCS, (HMENU)IDC_STATIC_CLOSELOCK, _T("🔒"), 2);
    pHHCloseLock = new HoverCursorHelper(hWndCloseLockStatic, IDC_HAND);

    hWndFitRightBottomStatic = CreateOptionFeatureStatic(hWnd, lpCS, (HMENU)IDC_STATIC_FITRIGHTBOTTOM, _T("↘"), 3);
    pHHFitRightBottom = new HoverCursorHelper(hWndFitRightBottomStatic, IDC_HAND);



    hWndCloseButton = CreateWindowEx( WS_EX_COMPOSITED, 
        _T("BUTTON"), _T("x"),
        BS_FLAT | BS_LEFTTEXT | WS_CHILD | WS_VISIBLE,
        MIN_WIDTH - CLOSE_BUTTON_WIDTH, 0, 
        CLOSE_BUTTON_WIDTH, CUSTOM_HEADER_HEIGHT,
        hWnd,
        (HMENU)IDC_CLOSE_BUTTON,
        lpCS->hInstance,
        NULL );

    SetWindowPos(hWndCloseButton, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    SetControlFonts();
}

// SetFont for symbol character.
void MainWindow::SetControlFonts()
{
    hFontOptStatic = CreateFont(16, 0, 0, 0,
                FW_NORMAL, FALSE, FALSE, 0,
                DEFAULT_CHARSET,
                OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY, DEFAULT_PITCH, 
                _T("Meiryo UI"));
    SendMessage(hWndZoomStatic, WM_SETFONT, (WPARAM)hFontOptStatic, MAKELPARAM(FALSE, 0));
    SendMessage(hWndTopMostStatic, WM_SETFONT, (WPARAM)hFontOptStatic, MAKELPARAM(FALSE, 0));
    SendMessage(hWndCloseLockStatic, WM_SETFONT, (WPARAM)hFontOptStatic, MAKELPARAM(FALSE, 0));
    SendMessage(hWndFitRightBottomStatic, WM_SETFONT, (WPARAM)hFontOptStatic, MAKELPARAM(FALSE, 0));
    SendMessage(hWndCloseButton, WM_SETFONT, (WPARAM)hFontOptStatic, MAKELPARAM(FALSE, 0));

}


// Set refresh timer.
void MainWindow::SetTimer(UINT elapse)
{
    ::SetTimer(hWnd, ID_TIMER, elapse, NULL);
}


// common function to create STATIC control.
HWND MainWindow::CreateOptionFeatureStatic(HWND hWndParent, LPCREATESTRUCT lpCS, HMENU idc, LPCTSTR caption, int index) {
    int featureButtonWidth = 16;
    int padding = 3;

    return CreateWindowEx( 0, 
        _T("STATIC"), caption,
	    SS_NOTIFY | SS_CENTER | SS_NOPREFIX | WS_CHILD | WS_VISIBLE,
	    padding + (padding + featureButtonWidth) * index, padding, 
        featureButtonWidth, CUSTOM_HEADER_HEIGHT - padding * 2,
	    hWndParent, 
        idc,
	    lpCS->hInstance, 
        NULL);
}


// when static control clicked.
// TODO: improve implement.
BOOL MainWindow::OnCtlColorStatic(HWND hWnd, HDC hdc) {

    if (hWnd == hWndZoomStatic) {
        // Toggle Zoom
        SetTextColor(hdc, 
            (IsDoubleSize ? RGB(255, 255, 255) : RGB(0, 0, 0)));
        SetBkColor(hdc, 
            (IsDoubleSize ? RGB(64, 196, 128) : RGB(128, 128, 128)));
        return (BOOL)(HBRUSH)GetStockObject(NULL_BRUSH);
    }

    if (hWnd == hWndTopMostStatic) {
        // Toggle TopMost
        SetTextColor(hdc, 
            (IsTopMost ? RGB(255, 255, 255) : RGB(0, 0, 0)));
        SetBkColor(hdc, 
            (IsTopMost ? RGB(64, 196, 128) : RGB(128, 128, 128)));
        return (BOOL)(HBRUSH)GetStockObject(NULL_BRUSH);
    }

    if (hWnd == hWndCloseLockStatic) {
        // Toggle Close Button Guard.
        // This feature only block click mistake. 
        // This feature does NOT block close event like select close menu from right click tasktray.
        SetTextColor(hdc, 
            (IsCloseLocked ? RGB(255, 255, 255) : RGB(0, 0, 0)));
        SetBkColor(hdc, 
            (IsCloseLocked ? RGB(64, 196, 128) : RGB(128, 128, 128)));
        return (BOOL)(HBRUSH)GetStockObject(NULL_BRUSH);
    }

    if (hWnd == hWndFitRightBottomStatic) {
        // Toggle bring back if window moved over the right bottom of screen.
        SetTextColor(hdc, 
            (IsFitRBEnabled ? RGB(255, 255, 255) : RGB(0, 0, 0)));
        SetBkColor(hdc, 
            (IsFitRBEnabled ? RGB(64, 196, 128) : RGB(128, 128, 128)));
        return (BOOL)(HBRUSH)GetStockObject(NULL_BRUSH);
    }

    return 0;
}

// WM_PAINT
void MainWindow::OnPaint(HWND hWnd, HDC hdc) {
    HDC hMdc;
    HBITMAP hbmp;

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

    MoveWindow(hWnd, 
        windowRect.left, windowRect.top,
        rc.right - rc.left, 
        rc.bottom - rc.top,
        FALSE);

    // static
    MoveWindow(hWndStatic, 
        0, 0,
        destsize.cx - CLOSE_BUTTON_WIDTH, 
        CUSTOM_HEADER_HEIGHT ,
        FALSE);
    
    // close button
    MoveWindow(hWndCloseButton, 
        destsize.cx - CLOSE_BUTTON_WIDTH, 0,
        CLOSE_BUTTON_WIDTH, 
        CUSTOM_HEADER_HEIGHT,
        FALSE);

    SetWindowPos(hWndCloseButton, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    // fill background
    RECT bodyRect;
    SetRect(&bodyRect, 0, CUSTOM_HEADER_HEIGHT, destsize.cx, destsize.cy + CUSTOM_HEADER_HEIGHT);
    FillRect(hdc, &bodyRect, appBlackBrush);

    //
    if (hbmp) {
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
        DeleteObject(hbmp);
    }

}


// capture NotificationArea's image.
// returns bitmap.
HBITMAP MainWindow::CaptureNotificationArea(_Out_ LPSIZEL const out_size){

    // I assume  Notify Tray's option button (button with triangle mark) was deployed very left of the area.
    LONG buttonWidth = GetNotifyTrayOptionButtonWidth();
    HWND target = findhelper.FindNotifyTrayHwnd(findhelper.Tray);


    HDC hTargetDC = GetWindowDC(target);
    HDC hMemoryDC = CreateCompatibleDC(hTargetDC);


    // ウィンドウ領域の取得
    RECT rect;
    GetWindowRect(target, &rect);


    // 
    LONG width = rect.right - rect.left + 1 - buttonWidth;
    LONG height = rect.bottom - rect.top + 1;

    // maybe worth checking these are positive values
    HBITMAP hBitmap = CreateCompatibleBitmap(hTargetDC, width, height);

    // get a new bitmap
    HBITMAP hOldBitmap = (HBITMAP) SelectObject(hMemoryDC, hBitmap);

    BitBlt(hMemoryDC, 0, 0, width, height, //destDC, x, y, w, h
        hTargetDC, buttonWidth, 0, // srcDC, x,y
        SRCCOPY);
    hBitmap = (HBITMAP) SelectObject(hMemoryDC, hOldBitmap);


    out_size->cx = width;
    out_size->cy = height;

    // clean up
    DeleteDC(hMemoryDC);
    // DeleteDC(hScreenDC); // for CreateDC
    ReleaseDC(target, hTargetDC);   // for GetDC / GetWindowDC

    // now your image is held in hBitmap. You can save it or do whatever with it
    return hBitmap;
}

// △ ボタンの幅。表示されてない場合は0。
// width of the button with triangle mark.
LONG MainWindow::GetNotifyTrayOptionButtonWidth()
{
    HWND button = findhelper.FindNotifyTrayHwnd(findhelper.OptButton);
    
    RECT rect;
    GetWindowRect(button, &rect);
    return rect.right - rect.left;
}



LRESULT MainWindow::OnCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if (LOWORD(wParam) == IDC_CLOSE_BUTTON) {
        if (!IsCloseLocked) {
            // CloseWindow(this->hWnd); // minimize
            DestroyWindow(this->hWnd);
        }
        return 0;
    }
    if (LOWORD(wParam) == IDC_STATIC_ZOOM) {
        switch(HIWORD(wParam)) {
        case STN_CLICKED:
            IsDoubleSize = !IsDoubleSize;
            break;
        case STN_DBLCLK:
            break;
        }
    }
    if (LOWORD(wParam) == IDC_STATIC_TOPMOST) {
        switch(HIWORD(wParam)) {
        case STN_CLICKED:
            IsTopMost = !IsTopMost;
            // クリックされてるのでふつうはアクティブだけど。
            SetWindowPos(this->hWnd, 
                (IsTopMost ? HWND_TOPMOST : HWND_NOTOPMOST), 
                0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
            break;
        case STN_DBLCLK:
            break;
        }
    }
    static TCHAR szHoldCloseButtonText[] = _T("🔒");
    static TCHAR szCloseButtonText[] = _T("x");

    if (LOWORD(wParam) == IDC_STATIC_FITRIGHTBOTTOM) {
        switch(HIWORD(wParam)) {
        case STN_CLICKED:
            IsFitRBEnabled = !IsFitRBEnabled;
            break;
        case STN_DBLCLK:
            break;
        }
    }


    if (LOWORD(wParam) == IDC_STATIC_CLOSELOCK) {
        switch(HIWORD(wParam)) {
        case STN_CLICKED:
            IsCloseLocked = !IsCloseLocked;
            SetWindowText(hWndCloseButton,  
                (IsCloseLocked ? szHoldCloseButtonText : szCloseButtonText)
                );
            EnableWindow(hWndCloseButton, !IsCloseLocked);

            break;
        case STN_DBLCLK:
            break;
        }
    }
    
    return 0;
}
