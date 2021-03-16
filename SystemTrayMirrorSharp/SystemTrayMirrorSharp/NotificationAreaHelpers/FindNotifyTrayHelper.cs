using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using static SystemTrayMirrorSharp.NativeMethods;

namespace SystemTrayMirrorSharp.NotificationAreaHelpers
{
    class FindNotifyTrayHelper
    {
        public enum TrayItems
        {
            Tray, 
            OptButton, 
            Sys, 
            User, 
            Clock,
        }

        public static IntPtr FindNotifyTrayHwnd(TrayItems @type)
        {
            IntPtr trayHandle = FindWindow("Shell_TrayWnd", "");
            trayHandle = FindWindowEx(trayHandle, IntPtr.Zero, "TrayNotifyWnd", null);

            // 通知アイコンの表示のためのボタン : triangle mark button to promote notification.
            IntPtr hWndButton = FindWindowEx(trayHandle, IntPtr.Zero, "Button", null);

            // システムによって昇格された通知領域 : "System Promoted Notification Area"
            IntPtr hWndNotifyAreaElevatedBySystem = FindWindowEx(trayHandle, IntPtr.Zero, "ToolbarWindow32", null);

            // ユーザーによって昇格された通知領域の親 : Parent Window of "User Promoted Notification Area"
            IntPtr hWndSysPager = FindWindowEx(trayHandle, IntPtr.Zero, "SysPager", null);
            // ユーザーによって昇格された通知領域 : "User Promoted Notification Area"
            IntPtr hWndNotifyAreaElevatedByUser = FindWindowEx(hWndSysPager, IntPtr.Zero, "ToolbarWindow32", null);

            // 時計 : Clock
            IntPtr hWndClock = FindWindowEx(trayHandle, IntPtr.Zero, "TrayClockWClass", null);

            switch (type)
            {
                case TrayItems.Tray:
                    return trayHandle;
                case TrayItems.OptButton:
                    return hWndButton;
                case TrayItems.Sys:
                    return hWndNotifyAreaElevatedBySystem;
                case TrayItems.User:
                    return hWndNotifyAreaElevatedByUser;
                case TrayItems.Clock:
                    return hWndClock;
                default:
                    return trayHandle;
            }
        }
    }
}
