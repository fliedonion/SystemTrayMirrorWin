using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using static SystemTrayMirrorSharp.NativeMethods;

namespace SystemTrayMirrorSharp.NotificationAreaHelpers
{
    class CaptureNotificationAreaHelper
    {
        const double zoomRate = 1.5;


        public Size CaptureNotificationArea(Graphics g, bool zoomed) {

            return CaptureNotificationArea(g, zoomed, false);
        }

        public Size GetNotificationAreaSize(bool zoomed)
        {
            return CaptureNotificationArea(null, zoomed, true);
        }


        public int GetNotifyTrayOptionButtonWidth()
        {
            IntPtr button = FindNotifyTrayHelper.FindNotifyTrayHwnd(FindNotifyTrayHelper.TrayItems.OptButton);

            RECT rect;
            GetWindowRect(button, out rect);
            return rect.right - rect.left;
        }


        private Size CaptureNotificationArea(Graphics g, bool zoomed, bool suppressDrawing)
        {
            int buttonWidth = GetNotifyTrayOptionButtonWidth();
            IntPtr hwndNotifyArea = FindNotifyTrayHelper.FindNotifyTrayHwnd(FindNotifyTrayHelper.TrayItems.Tray);

            RECT rect;
            GetWindowRect(hwndNotifyArea, out rect);

            int width = rect.right - rect.left - buttonWidth;
            int height = rect.bottom - rect.top + 1;

            int destWidth = width;
            int destHeight = height;

            if (zoomed)
            {
                destWidth = (int)(width * zoomRate);
                destHeight = (int)(height * zoomRate);
            }

            if (!suppressDrawing && g != null)
            {
                IntPtr hMemoryDC = g.GetHdc();
                IntPtr hTargetDC = GetDC(hwndNotifyArea);

                if (!zoomed)
                {
                    BitBlt(hMemoryDC, 0, 0, width, height, //destDC, x, y, w, h
                            hTargetDC, buttonWidth, 0, // srcDC, x,y
                            RasterOps.SRCCOPY);

                }
                else
                {
                    // int oldBltMode = SetStretchBltMode(hdc, HALFTONE);

                    StretchBlt(hMemoryDC, 0, 0, destWidth, destHeight,
                               hTargetDC, buttonWidth, 0, width, height,
                               RasterOps.SRCCOPY);

                    // if (oldBltMode != 0)
                    // {
                    //     SetStretchBltMode(hdc, oldBltMode);
                    // }

                }





                g.ReleaseHdc(hMemoryDC);
                ReleaseDC(hwndNotifyArea, hTargetDC);
            }

            return new Size(destWidth, destHeight);
        }

    }
}
