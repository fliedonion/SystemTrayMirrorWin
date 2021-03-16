using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;

namespace SystemTrayMirrorSharp.Controls
{
    [System.ComponentModel.DesignerCategory("Code")]
    public class OptionFeatureButton : Label
    {
        public event EventHandler CheckChanged;
        private bool checkedValue = false;


        public OptionFeatureButton()
        {
            SetColor();
        }


        public bool Checked { 
            get => checkedValue;
            set
            {
                if (checkedValue != value)
                {
                    checkedValue = value;
                    CheckChanged?.Invoke(this, EventArgs.Empty);
                }
            }
        }


        protected override void OnClick(EventArgs e)
        {
            base.OnClick(e);

            Checked = !Checked;
            SetColor();
            
        }

        private void SetColor()
        {
            BackColor = Checked ? Color.FromArgb(64, 196, 128) : Color.FromArgb(128, 128, 128);
            ForeColor = Checked ? Color.FromArgb(255, 255, 255) : Color.FromArgb(0, 0, 0);
        }

    }
}
