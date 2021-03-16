using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SystemTrayMirrorSharp
{
    public partial class SystemTrayMirror : Form
    {
        private readonly int altTitleHeight = 20;


        public SystemTrayMirror()
        {
            InitializeComponent();

            altTitleHeight = titleBarPanel.Height;
            zoomFeatureButton.CheckChanged += ZoomFeatureButton_CheckChanged;
            topMostButton.CheckChanged += TopMostButton_CheckChanged;
            closeLockButton.CheckChanged += CloseLockButton_CheckChanged;


            redrawTimer.Enabled = true;
        }

        private void CloseLockButton_CheckChanged(object sender, EventArgs e)
        {
            closeButton.Enabled = !closeButton.Enabled;
            SetCloseButtonStyle();
        }


        private void SetCloseButtonStyle()
        {
            closeButton.Text = closeButton.Enabled ? "x" : "🔒";
            closeButton.BackColor =
                closeButton.Enabled ? Color.FromArgb(240, 80, 80) : Color.FromArgb(128, 128, 128);
            closeButton.FlatAppearance.BorderColor =
                closeButton.Enabled ? Color.FromArgb(128, 64, 64) : Color.FromArgb(64, 64, 64);

        }


        private void TopMostButton_CheckChanged(object sender, EventArgs e)
        {
            TopMost = !TopMost;
        }

        private void ZoomFeatureButton_CheckChanged(object sender, EventArgs e)
        {
            notificationAreaMirror1.Zoomed = zoomFeatureButton.Checked;
        }

        // "🔒" "x" "🔍" "📌" "🔒" "↘"

        protected override void OnShown(EventArgs e)
        {
            base.OnShown(e);
        }

        private void redrawTimer_Tick(object sender, EventArgs e)
        {
            DrawItems();
        }

        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            base.OnFormClosing(e);
            redrawTimer.Enabled = false;
        }


        protected override void OnPaintBackground(PaintEventArgs e)
        {
            // base.OnPaintBackground(e);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            // base.OnPaint(e);
            DrawItems();
        }

        private void DrawItems()
        {

            if (!Visible) return;

            var size = notificationAreaMirror1.UpdateArea();
            this.Width = size.Width - 1;
            this.Height = altTitleHeight + size.Height - 1;

            titleBarPanel.Refresh();
            notificationAreaMirror1.Refresh();
        }


        private void closeButton_Click(object sender, EventArgs e)
        {
            Close();
        }






        private const int WM_NCLBUTTONDOWN = 0xA1;
        private const int HT_CAPTION = 0x2;

        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        private static extern IntPtr SendMessage(
            IntPtr hWnd, int Msg, IntPtr wParam, IntPtr lParam);
        [DllImportAttribute("user32.dll")]
        private static extern bool ReleaseCapture();


        private void titleBarPanel_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                //マウスのキャプチャを解除
                ReleaseCapture();
                //タイトルバーでマウスの左ボタンが押されたことにする
                SendMessage(Handle, WM_NCLBUTTONDOWN, (IntPtr)HT_CAPTION, IntPtr.Zero);
            }
        }


    }
}
