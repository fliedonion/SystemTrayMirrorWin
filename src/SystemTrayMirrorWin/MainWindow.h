#pragma once
#include <windows.h>
#include <string.h>
#include <tchar.h>
#include <vector>

#include "ResourceId.h"

#include "FindNotifyTrayHelper.h"
#include "HoverCursorHelper.h"

// Constants

#define CLOSE_BUTTON_WIDTH 32
#define MIN_WIDTH 128
#define MIN_HEIGHT 48

// vc2013 not support constexpr
// int constexpr HEADER_HEIGHT = 24;
#define CUSTOM_HEADER_HEIGHT 24



class MainWindow
{
public:
    MainWindow();
    ~MainWindow();

    HINSTANCE hInst {};
    HWND hWnd {};  // hWnd = 0 / hWnd = NULL  does not work for public member.
    UINT TimerInterval = 200;

    // methods
    void OnCreate(WPARAM wParam, LPARAM lParam);
    void AddControls(LPCREATESTRUCT lpCS);
    void SetTimer(UINT elapse);

    void OnPaint(HWND hWnd, HDC hdc);
    BOOL OnCtlColorStatic(HWND hWnd, HDC hdc);
    LRESULT OnCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    void SetControlFonts();
    HBITMAP CaptureNotificationArea(_Out_ LPSIZEL const out_size);
    void UpdateByTimer();


private:
    // control handles
    HWND hWndStatic {};
    HWND hWndCloseButton {};

    // Option feature static Handles.
    HWND hWndZoomStatic {};
    HWND hWndTopMostStatic {};
    HWND hWndCloseLockStatic {};
    HWND hWndFitRightBottomStatic {};

    // resource handles
    HFONT hFontOptStatic, hFontDefault;

    HBITMAP hbmp {};

    // variables
    HoverCursorHelper* pHHTopMost = NULL;
    HoverCursorHelper* pHHZoom = NULL;
    HoverCursorHelper* pHHCloseLock = NULL;
    HoverCursorHelper* pHHFitRightBottom = NULL;
    FindNotifyTrayHelper findhelper;
    HBRUSH appBlackBrush = NULL;


    // state flags
    BOOL IsDoubleSize = FALSE;
    BOOL IsTopMost = FALSE;
    BOOL IsCloseLocked = FALSE;
    BOOL IsFitRBEnabled = FALSE;


    // methods
    HWND CreateOptionFeatureStatic(HWND hWndParent, LPCREATESTRUCT lpCS, HMENU idc, LPCTSTR caption, int index);
    LONG GetNotifyTrayOptionButtonWidth();

    void DrawTitleBar(HWND hWndWantToUpdate, const std::vector<HWND> &staticHandles, HWND closeButton);
    void DrawTitleBar(HDC hDCOfHWndWantToUpdate, const std::vector<HWND> &staticHandles, HWND closeButton);
    void DrawStaticToMemoryDC(HDC destDC, HWND hwndStatic);

    static RECT GetLocation(HWND hWnd);

};

