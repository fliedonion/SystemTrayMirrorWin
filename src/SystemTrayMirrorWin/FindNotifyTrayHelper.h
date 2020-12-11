#pragma once
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>


class FindNotifyTrayHelper
{
public:
    FindNotifyTrayHelper();
    enum TrayItems { Tray, OptButton, Sys, User, Clock }; // non Scoped enum
    HWND FindNotifyTrayHwnd(TrayItems type);
    // enum class TrayItems { Tray, OptButton, Sys, User, Clock }; // Scoped enum
    ~FindNotifyTrayHelper();
};
