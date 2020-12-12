#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

#include "FindNotifyTrayHelper.h"
#include "HoverCursorHelper.h"

#include "Main.h"



MainWindow* pMainWindow;

int CALLBACK WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPSTR     lpCmdLine,
   _In_ int       nCmdShow
)
{
    
    TCHAR szWindowClass[] = _T("SystemTrayMirror");
    TCHAR szTitle[] = _T("SystemTray Mirror");


    MainWindow* pMW = pMainWindow = new MainWindow();
    
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("RegisterClassEx failed!"),
            szTitle,
            NULL);

        return 1;
    }

    pMW->hInst = hInstance;

    HWND hWnd = CreateWindowEx(
        WS_EX_COMPOSITED, // double buffer
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW & ~WS_MINIMIZEBOX & ~WS_MAXIMIZEBOX, 
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 100,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("CreateWindow failed!"),
            szTitle,
            NULL);

        return 1;
    }
    // pMW->hWnd = hWnd; // CreateWindowEx raise WM_CREATE. So, we pass the hWnd to pMainWindow's OnCreate method instead of here.


    SetWindowLong(hWnd, GWL_STYLE, WS_POPUP | WS_MINIMIZEBOX);
    SetWindowLong(hWnd, GWL_EXSTYLE, 0);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}
