namespace SystemTrayMirrorSharp
{
    partial class SystemTrayMirror
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージド リソースを破棄する場合は true を指定し、その他の場合は false を指定します。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.closeButton = new System.Windows.Forms.Button();
            this.titleBarPanel = new System.Windows.Forms.Panel();
            this.redrawTimer = new System.Windows.Forms.Timer(this.components);
            this.zoomFeatureButton = new SystemTrayMirrorSharp.Controls.OptionFeatureButton();
            this.notificationAreaMirror1 = new SystemTrayMirrorSharp.Controls.NotificationAreaMirror();
            this.topMostButton = new SystemTrayMirrorSharp.Controls.OptionFeatureButton();
            this.closeLockButton = new SystemTrayMirrorSharp.Controls.OptionFeatureButton();
            this.titleBarPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // closeButton
            // 
            this.closeButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.closeButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(240)))), ((int)(((byte)(80)))), ((int)(((byte)(80)))));
            this.closeButton.FlatAppearance.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.closeButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.closeButton.ForeColor = System.Drawing.Color.White;
            this.closeButton.Location = new System.Drawing.Point(215, 0);
            this.closeButton.Margin = new System.Windows.Forms.Padding(0);
            this.closeButton.Name = "closeButton";
            this.closeButton.Size = new System.Drawing.Size(41, 20);
            this.closeButton.TabIndex = 3;
            this.closeButton.Text = "x";
            this.closeButton.UseVisualStyleBackColor = false;
            this.closeButton.Click += new System.EventHandler(this.closeButton_Click);
            // 
            // titleBarPanel
            // 
            this.titleBarPanel.Controls.Add(this.closeLockButton);
            this.titleBarPanel.Controls.Add(this.topMostButton);
            this.titleBarPanel.Controls.Add(this.zoomFeatureButton);
            this.titleBarPanel.Controls.Add(this.closeButton);
            this.titleBarPanel.Dock = System.Windows.Forms.DockStyle.Top;
            this.titleBarPanel.Location = new System.Drawing.Point(0, 0);
            this.titleBarPanel.Margin = new System.Windows.Forms.Padding(0);
            this.titleBarPanel.Name = "titleBarPanel";
            this.titleBarPanel.Size = new System.Drawing.Size(256, 20);
            this.titleBarPanel.TabIndex = 5;
            this.titleBarPanel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.titleBarPanel_MouseDown);
            // 
            // redrawTimer
            // 
            this.redrawTimer.Tick += new System.EventHandler(this.redrawTimer_Tick);
            // 
            // zoomFeatureButton
            // 
            this.zoomFeatureButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(128)))), ((int)(((byte)(128)))));
            this.zoomFeatureButton.Checked = false;
            this.zoomFeatureButton.Font = new System.Drawing.Font("Meiryo UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.zoomFeatureButton.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))));
            this.zoomFeatureButton.Location = new System.Drawing.Point(3, 2);
            this.zoomFeatureButton.Margin = new System.Windows.Forms.Padding(0);
            this.zoomFeatureButton.Name = "zoomFeatureButton";
            this.zoomFeatureButton.Size = new System.Drawing.Size(16, 16);
            this.zoomFeatureButton.TabIndex = 6;
            this.zoomFeatureButton.Text = "🔍";
            // 
            // notificationAreaMirror1
            // 
            this.notificationAreaMirror1.Location = new System.Drawing.Point(0, 20);
            this.notificationAreaMirror1.Margin = new System.Windows.Forms.Padding(0);
            this.notificationAreaMirror1.Name = "notificationAreaMirror1";
            this.notificationAreaMirror1.Size = new System.Drawing.Size(206, 48);
            this.notificationAreaMirror1.TabIndex = 4;
            this.notificationAreaMirror1.Text = "notificationAreaMirror1";
            this.notificationAreaMirror1.Zoomed = false;
            // 
            // topMostButton
            // 
            this.topMostButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(128)))), ((int)(((byte)(128)))));
            this.topMostButton.Checked = false;
            this.topMostButton.Font = new System.Drawing.Font("Meiryo UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.topMostButton.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))));
            this.topMostButton.Location = new System.Drawing.Point(22, 2);
            this.topMostButton.Margin = new System.Windows.Forms.Padding(0);
            this.topMostButton.Name = "topMostButton";
            this.topMostButton.Size = new System.Drawing.Size(16, 16);
            this.topMostButton.TabIndex = 7;
            this.topMostButton.Text = "📌";
            // 
            // closeLockButton
            // 
            this.closeLockButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(128)))), ((int)(((byte)(128)))));
            this.closeLockButton.Checked = false;
            this.closeLockButton.Font = new System.Drawing.Font("Meiryo UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.closeLockButton.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))));
            this.closeLockButton.Location = new System.Drawing.Point(41, 2);
            this.closeLockButton.Margin = new System.Windows.Forms.Padding(0);
            this.closeLockButton.Name = "closeLockButton";
            this.closeLockButton.Size = new System.Drawing.Size(16, 16);
            this.closeLockButton.TabIndex = 8;
            this.closeLockButton.Text = "🔒";
            // 
            // SystemTrayMirror
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(256, 101);
            this.Controls.Add(this.titleBarPanel);
            this.Controls.Add(this.notificationAreaMirror1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "SystemTrayMirror";
            this.Text = "Form1";
            this.titleBarPanel.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Button closeButton;
        private SystemTrayMirrorSharp.Controls.NotificationAreaMirror notificationAreaMirror1;
        private System.Windows.Forms.Panel titleBarPanel;
        private System.Windows.Forms.Timer redrawTimer;
        private SystemTrayMirrorSharp.Controls.OptionFeatureButton zoomFeatureButton;
        private Controls.OptionFeatureButton closeLockButton;
        private Controls.OptionFeatureButton topMostButton;
    }
}

