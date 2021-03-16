using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using SystemTrayMirrorSharp.NotificationAreaHelpers;

namespace SystemTrayMirrorSharp.Controls
{

    [System.ComponentModel.DesignerCategory("Code")]
    public class NotificationAreaMirror : Label
    {
        public bool Zoomed { get; set; } = false;

        private CaptureNotificationAreaHelper paintHelper = new CaptureNotificationAreaHelper();

        public NotificationAreaMirror()
        {
            Text = "";
        }

        public Size UpdateArea()
        {
            return (this.Size = paintHelper.GetNotificationAreaSize(Zoomed));
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            paintHelper.CaptureNotificationArea(
                e.Graphics, Zoomed
                );
        }

    }
}
