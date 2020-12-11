#pragma once

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

#include "FindNotifyTrayHelper.h"
#include "HoverCursorHelper.h"

#include "ResourceId.h"
#include "MainWindow.h"

// variables
extern MainWindow* pMainWindow;

// prototypes
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HWND FindNotifyTray(FindNotifyTrayHelper::TrayItems type);
