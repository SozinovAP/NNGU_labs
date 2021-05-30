using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics.Tracing;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using OpenTK.Graphics.ES10;

namespace CompGraph_lab2
{
    public partial class Form1 : Form
    {
        private Bin tomo;
        private bool loaded;
        private View view;
        private int currentLayer;
        private int FrameCount;
        private DateTime NextFPSUpdate;

        public Form1()
        {
            InitializeComponent();
            loaded = false;
            currentLayer = 0;
            view = new View();
            tomo = new Bin();
            view.MinTF = TrackBar_minTF.Value;
            view.WidthTF = TrackBar_WidthTF.Value;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Application.Idle += Application_Idle;
            View.SetupView(glControl1.Width, glControl1.Height);
            glControl1.SwapBuffers();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                string str = dialog.FileName;
                tomo.ReadBIN(str);
                View.SetupView(glControl1.Width, glControl1.Height);
                loaded = true;
                glControl1.Invalidate();
                LayerTomo.Maximum = Bin.z - 1;
            }
        }

        private bool needReload = false;
        private void glControl1_Paint(object sender, PaintEventArgs e)
        {
            view.Update();
            if (loaded)
            {
                if (QuadsV.Checked)
                {
                    view.DrawQuads(currentLayer);
                }
                else if (TextureV.Checked)
                {
                    if (needReload)
                    {
                        view.generateTextureImage(currentLayer);
                        view.Load2DTexture();
                        needReload = false;
                    }
                    view.DrawTexture();
                }
            }
            glControl1.SwapBuffers();
        }

        void Application_Idle(object sender, EventArgs e)
        {
            while (glControl1.IsIdle)
            {
                displayFPS();
                glControl1.Invalidate();
            }
        }

        void displayFPS()
        {
            if (DateTime.Now >= NextFPSUpdate)
            {
                this.Text = String.Format("CT Visualiser (fps = {0})", FrameCount);
                NextFPSUpdate = DateTime.Now.AddSeconds(1);
                FrameCount = 0;
            }
            FrameCount++;
        }
        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            currentLayer = LayerTomo.Value;
            needReload = true;
        }

        private void TrackBar_minTF_Scroll(object sender, EventArgs e)
        { 
            label2.Text = TrackBar_minTF.Value.ToString();
            view.MinTF = TrackBar_minTF.Value;
            needReload = true;

        }

        private void TrackBar_WidthTF_Scroll(object sender, EventArgs e)
        {
           label3.Text = TrackBar_WidthTF.Value.ToString();
           view.WidthTF = TrackBar_WidthTF.Value;
           needReload = true;

        }

        private void glControl1_Load(object sender, EventArgs e)
        {
           
        }

        private void Form1_Resize(object sender, EventArgs e)
        {
            view.Update();
            View.SetupView(glControl1.Width, glControl1.Height);
            if (loaded)
            {
                if (QuadsV.Checked)
                {
                    view.DrawQuads(currentLayer);
                }
                else if (TextureV.Checked)
                {
                    if (needReload)
                    {
                        view.generateTextureImage(currentLayer);
                        view.Load2DTexture();
                        needReload = false;
                    }
                    view.DrawTexture();
                }
            }
            else
            {
                view.DrawTexture();
            }
            glControl1.SwapBuffers();

        }

        private void glControl1_Resize(object sender, EventArgs e)
        {
            if (Form1.ActiveForm != null)
            {
                int SizeW = this.Width - 48 - 93;
                int SizeH = (int) (this.Height * 0.7);

                if (SizeH * 1.3 < SizeW)
                {
                    SizeW = (int) (SizeH * 1.3);
                }
                else
                {
                    SizeH = (int) (SizeW / 1.3);
                }

                glControl1.Width = SizeW;
                glControl1.Height = SizeH;
            }
        }
    }
}
