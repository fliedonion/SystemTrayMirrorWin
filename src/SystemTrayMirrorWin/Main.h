#pragma once

#include <windows.h>
#include <tchar.h>

#include <cstdlib>
#include <cstring>

#include "FindNotifyTrayHelper.h"
#include "HoverCursorHelper.h"

#include "ResourceId.h"
#include "MainWindow.h"

// variables
extern MainWindow* pMainWindow;

// prototypes
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HWND FindNotifyTray(FindNotifyTrayHelper::TrayItems type);
