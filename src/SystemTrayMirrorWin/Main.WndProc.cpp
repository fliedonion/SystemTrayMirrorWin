#include "Main.h"


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;

    BOOL handled = FALSE;
    

    MainWindow* pMW = pMainWindow;

    switch (message)
    {
    case WM_CREATE:
        {
            if (hWnd && pMW->hWnd == NULL) {
                pMW->hWnd = hWnd;
                pMW->TimerInterval = 200;
                pMW->OnCreate(wParam, lParam);
                pMW->UpdateByTimer();
            }
        }
        break;
    case WM_COMMAND:
        return pMW->OnCommand(hWnd, message, wParam, lParam);

    case WM_NCHITTEST:
        return HTCAPTION;
        // return HTNOWHERE; // ignore


	case WM_TIMER:
        pMW->UpdateByTimer();
		return 0;

    case WM_CTLCOLORSTATIC: {
            HWND hWnd = (HWND)lParam;
            HDC hdc = (HDC)wParam;
            return pMW->OnCtlColorStatic(hWnd, hdc);
        }
        return FALSE;

    case WM_ERASEBKGND:
        // 背景の描画を処理したことにする(ちらつき防止。すべてを描画するので背景クリアの必要がない）
			return TRUE;

    case WM_NCPAINT:
            return TRUE;
    case WM_PAINT: {
            if(hWnd == pMW->hWnd) {
                PAINTSTRUCT ps;
                hdc = BeginPaint(hWnd, &ps);
                pMW->OnPaint(hWnd, hdc);
                EndPaint(hWnd, &ps);
            }
        }


        break;
	case WM_DESTROY:

        if (pMainWindow) delete pMainWindow;
        

        PostQuitMessage(0);
		return 0;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}

