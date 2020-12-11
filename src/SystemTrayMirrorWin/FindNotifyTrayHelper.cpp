#include "FindNotifyTrayHelper.h"


FindNotifyTrayHelper::FindNotifyTrayHelper()
{
}


FindNotifyTrayHelper::~FindNotifyTrayHelper()
{
}

HWND FindNotifyTrayHelper::FindNotifyTrayHwnd(FindNotifyTrayHelper::TrayItems type) {
    HWND trayHandle = FindWindow( _T("Shell_TrayWnd"), _T(""));
    trayHandle = FindWindowEx(trayHandle, 0, _T("TrayNotifyWnd"), NULL);

    // 通知アイコンの表示のためのボタン : triangle mark button to promote notification.
    HWND hWndButton = FindWindowEx(trayHandle, 0, _T("Button"), NULL);
    
    // システムによって昇格された通知領域 : "System Promoted Notification Area"
    HWND hWndNotifyAreaElevatedBySystem = FindWindowEx(trayHandle, 0, _T("ToolbarWindow32"), NULL);

    // ユーザーによって昇格された通知領域の親 : Parent Window of "User Promoted Notification Area"
    HWND hWndSysPager = FindWindowEx(trayHandle, 0, _T("SysPager"), NULL);
    // ユーザーによって昇格された通知領域 : "User Promoted Notification Area"
    HWND hWndNotifyAreaElevatedByUser = FindWindowEx(hWndSysPager, 0, _T("ToolbarWindow32"), NULL);

    // 時計 : Clock
    HWND hWndClock = FindWindowEx(trayHandle, 0, _T("TrayClockWClass"), NULL);

    switch(type) {
    case Tray:
        return trayHandle;
    case OptButton:
        return hWndButton;
    case Sys:
        return hWndNotifyAreaElevatedBySystem;
    case User:
        return hWndNotifyAreaElevatedByUser;
    case Clock:
        return hWndClock;
    default:
        return trayHandle;
    }
}