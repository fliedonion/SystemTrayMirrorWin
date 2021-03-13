#include "MainWindow.h"


extern std::vector<HWND> staticHandles;


// common function to create STATIC control.
HWND MainWindow::CreateOptionFeatureStatic(
        HWND hWndParent, LPCREATESTRUCT lpCS, HMENU idc, LPCTSTR caption, int index) {
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


void MainWindow::AddControls(LPCREATESTRUCT lpCS){

    int idx = 0;
    staticHandles.push_back(
            hWndZoomStatic = CreateOptionFeatureStatic(hWnd, lpCS, (HMENU)IDC_STATIC_ZOOM, _T("🔍"), idx++));
    pHHZoom = new HoverCursorHelper(hWndZoomStatic, IDC_HAND);

    staticHandles.push_back(
            hWndTopMostStatic = CreateOptionFeatureStatic(hWnd, lpCS, (HMENU)IDC_STATIC_TOPMOST, _T("📌"), idx++));
    pHHTopMost = new HoverCursorHelper(hWndTopMostStatic, IDC_HAND);

    staticHandles.push_back(
            hWndCloseLockStatic = CreateOptionFeatureStatic(hWnd, lpCS, (HMENU)IDC_STATIC_CLOSELOCK, _T("🔒"), idx++));
    pHHCloseLock = new HoverCursorHelper(hWndCloseLockStatic, IDC_HAND);

    staticHandles.push_back(
            hWndFitRightBottomStatic = CreateOptionFeatureStatic(hWnd, lpCS, (HMENU)IDC_STATIC_FITRIGHTBOTTOM, _T("↘"), idx++));
    pHHFitRightBottom = new HoverCursorHelper(hWndFitRightBottomStatic, IDC_HAND);


    hWndCloseButton = CreateWindowEx( 0,
                                      _T("BUTTON"), _T("x"),
                                      BS_FLAT | BS_LEFTTEXT | WS_CHILD | WS_VISIBLE,
                                      MIN_WIDTH - CLOSE_BUTTON_WIDTH, 0,
                                      CLOSE_BUTTON_WIDTH, CUSTOM_HEADER_HEIGHT,
                                      hWnd,
                                      (HMENU)IDC_CLOSE_BUTTON,
                                      lpCS->hInstance,
                                      NULL );

    SetWindowPos(hWndCloseButton, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOCOPYBITS | SWP_NOREDRAW);
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


// when static control clicked.
// TODO: improve implement.
BOOL MainWindow::OnCtlColorStatic(HWND hWnd, HDC hdc) {

    static COLORREF offBkColor = RGB(128, 128, 128);
    static COLORREF offFgColor = RGB(0, 0, 0);
    static COLORREF onBkColor = RGB(64, 196, 128);
    static COLORREF onFgColor = RGB(255, 255, 255);

    static HBRUSH hOffBkBrush = CreateSolidBrush(offBkColor);
    static HBRUSH hOnBkBrush = CreateSolidBrush(onBkColor);


    bool shouldProc = false;
    BOOL isOn = FALSE;

    if (hWnd == hWndZoomStatic) {
        // Toggle Zoom
        shouldProc = true;
        isOn = IsDoubleSize;
    }

    if (hWnd == hWndTopMostStatic) {
        // Toggle TopMost
        shouldProc = true;
        isOn = IsTopMost;
    }

    if (hWnd == hWndCloseLockStatic) {
        // Toggle Close Button Guard.
        // This feature only block click mistake.
        // This feature does NOT block close event like select close menu from right click tasktray.
        shouldProc = true;
        isOn = IsCloseLocked;
    }

    if (hWnd == hWndFitRightBottomStatic) {
        // Toggle bring back if window moved over the right bottom of screen.
        shouldProc = true;
        isOn = IsFitRBEnabled;
    }

    //
    if (shouldProc) {
        if (isOn) {
            SetTextColor(hdc, onFgColor);
            SetBkColor(hdc, onBkColor);

            return (BOOL)(INT_PTR)hOnBkBrush;
        }

        SetTextColor(hdc, offFgColor);
        SetBkColor(hdc, offBkColor);
        return (BOOL)(INT_PTR)hOffBkBrush;
    }

    return 0;
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
                             0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE
                                         | SWP_NOCOPYBITS
                                         | SWP_NOREDRAW
                                         | SWP_NOOWNERZORDER);
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

