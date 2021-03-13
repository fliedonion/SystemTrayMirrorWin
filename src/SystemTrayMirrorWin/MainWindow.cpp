#include "MainWindow.h"

extern std::vector<HWND> staticHandles;
extern std::vector<HBITMAP> deleteReservedBmp;

MainWindow::MainWindow() {

}

MainWindow::~MainWindow()
{
    if (pHHZoom) delete pHHZoom;
    if (pHHTopMost) delete pHHTopMost;
    if (pHHCloseLock) delete pHHCloseLock;
    if (pHHFitRightBottom) delete pHHFitRightBottom;

    KillTimer(hWnd, ID_TIMER);
    for(HBITMAP hbmp4del: deleteReservedBmp) {
        DeleteObject(hbmp4del);
    }

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


// Set refresh timer.
void MainWindow::SetTimer(UINT elapse)
{
    ::SetTimer(hWnd, ID_TIMER, elapse, NULL);
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


