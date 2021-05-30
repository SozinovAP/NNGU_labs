using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        private View view = new View();

        public Form1()
        {
            InitializeComponent();
        }

        private void glControl1_Load(object sender, EventArgs e)
        {
            view.Setup(glControl1.Width, glControl1.Height);

            view.InitShader();

        }

        private void glControl1_Paint(object sender, PaintEventArgs e)
        {
            view.Update();

            glControl1.SwapBuffers();
        }

        private void Form1_Resize(object sender, EventArgs e)
        {
            view.Setup(glControl1.Width, glControl1.Height);
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked)
            {
                view.SetCubView(1);
                view.Update();

                glControl1.SwapBuffers();
            }
        }

        private void radioButton4_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked)
            {
                view.SetCubView(3);
                view.Update();

                glControl1.SwapBuffers();
            }
        }

        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked)
            {
                view.SetCubView(2);
                view.Update();

                glControl1.SwapBuffers();
            }
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked)
            {
                view.SetCubView(0);
                view.Update();

                glControl1.SwapBuffers();
            }
        }

        private void BigSphere_off_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked)
            {
                view.SetBigSphere(0);
                view.Update();

                glControl1.SwapBuffers();
            }
        }

        private void BigSphere_diff_CheckedChange(object sender, EventArgs e)
        {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked)
            {
                view.SetBigSphere(1);
                view.Update();

                glControl1.SwapBuffers();
            }
        }

        private void BigSphere_mir_CheckedChange(object sender, EventArgs e)
        {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked)
            {
                view.SetBigSphere(2);
                view.Update();

                glControl1.SwapBuffers();
            }
        }

        private void BigSphere_refr_CheckedChange(object sender, EventArgs e)
        {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked)
            {
                view.SetBigSphere(3);
                view.Update();

                glControl1.SwapBuffers();
            }
        }

        private void SmallSphere_off_CheckedChange(object sender, EventArgs e)
        {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked)
            {
                view.SetSmallSphere(0);
                view.Update();

                glControl1.SwapBuffers();
            }
        }

        private void SmallSphere_dif_CheckedChange(object sender, EventArgs e)
        {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked)
            {
                view.SetSmallSphere(1);
                view.Update();

                glControl1.SwapBuffers();
            }
        }

        private void SmallSphere_mir_CheckedChange(object sender, EventArgs e)
        {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked)
            {
                view.SetSmallSphere(2);
                view.Update();

                glControl1.SwapBuffers();
            }
        }

        private void SmallSphere_refr_CheckedChange(object sender, EventArgs e)
        {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked)
            {
                view.SetSmallSphere(3);
                view.Update();

                glControl1.SwapBuffers();
            }
        }

        private void SmallThetr_off_CheckedChange(object sender, EventArgs e)
        {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked)
            {
                view.SetThetr(0);
                view.Update();

                glControl1.SwapBuffers();
            }
        }

        private void SmallThetr_dif_CheckedChange(object sender, EventArgs e)
        {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked)
            {
                view.SetThetr(1);
                view.Update();

                glControl1.SwapBuffers();
            }
        }

        private void SmallThetr_mir_CheckedChange(object sender, EventArgs e)
        {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked)
            {
                view.SetThetr(2);
                view.Update();

                glControl1.SwapBuffers();
            }
        }

        private void SmallThetr_refr_CheckedChange(object sender, EventArgs e)
        {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked)
            {
                view.SetThetr(3);
                view.Update();

                glControl1.SwapBuffers();
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            double x, y, z, refl, refr;
            if (reflcub.TextLength > 0)
            {
                if (double.TryParse(reflcub.Text, out refl))
                {
                    if (refl < 0.0)
                    {
                        reflcub.Text = "0,0";
                        refl = 0.0;
                    }
                }
                else
                {
                    reflcub.Text = "0,0";
                    refl = 0.0;
                }
            }
            else
            {
                reflcub.Text = "0,0";
                refl = 0.0;
            }

            if (refrcub.TextLength > 0)
            {
                if (double.TryParse(refrcub.Text, out refr))
                {
                    if (refr < 0.0)
                    {
                        refrcub.Text = "0,0";
                        refr = 0.0;
                    }
                }
                else
                {
                    refrcub.Text = "0,0";
                    refr = 0.0;
                }
            }
            else
            {
                refrcub.Text = "0,0";
                refr = 0.0;
            }

            if (Cubr.TextLength > 0)
            {
                if (double.TryParse(Cubr.Text, out x))
                {
                    if (x < 0.0)
                    {
                        Cubr.Text = "0,0";
                        x = 0.0;
                    }
                    else if (x > 1.0)
                    {
                        Cubr.Text = "1,0";
                        x = 0.0;
                    }
                }
                else
                {
                    Cubr.Text = "0,0";
                    x = 0.0;
                }
            }
            else
            {
                Cubr.Text = "0,0";
                x = 0.0;
            }

            if (Cubg.TextLength > 0)
            {
                if (double.TryParse(Cubg.Text, out y))
                {
                    if (y < 0.0)
                    {
                        Cubg.Text = "0,0";
                        y = 0.0;
                    }
                    else if (y > 1.0)
                    {
                        Cubg.Text = "1,0";
                        y = 0.0;
                    }
                }
                else
                {
                    Cubg.Text = "0,0";
                    y = 0.0;
                }
            }
            else
            {
                Cubg.Text = "0,0";
                y = 0.0;
            }

            if (Cubb.TextLength > 0)
            {
                if (double.TryParse(Cubb.Text, out z))
                {
                    if (z < 0.0)
                    {
                        Cubb.Text = "0,0";
                        z = 0.0;
                    }
                    else if (z > 1.0)
                    {
                        Cubb.Text = "1,0";
                        z = 0.0;
                    }
                }
                else
                {
                    Cubb.Text = "0,0";
                    z = 0.0;
                }
            }
            else
            {
                Cubb.Text = "0,0";
                z = 0.0;
            }
            view.SetColCub((float)x, (float)y, (float)z, (float)refl, (float)refr);
            view.Update();

            glControl1.SwapBuffers();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            depth.Text = trackBar1.Value.ToString();
            view.SetDepth(trackBar1.Value);
            view.Update();

            glControl1.SwapBuffers();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            double x, y, z, refl, refr;
            if (reflbs.TextLength > 0)
            {
                if (double.TryParse(reflbs.Text, out refl))
                {
                    if (refl < 0.0)
                    {
                        reflbs.Text = "0,0";
                        refl = 0.0;
                    }
                }
                else
                {
                    reflbs.Text = "0,0";
                    refl = 0.0;
                }
            }
            else
            {
                reflbs.Text = "0,0";
                refl = 0.0;
            }

            if (refrbs.TextLength > 0)
            {
                if (double.TryParse(refrbs.Text, out refr))
                {
                    if (refr < 0.0)
                    {
                        refrbs.Text = "0,0";
                        refr = 0.0;
                    }
                }
                else
                {
                    refrbs.Text = "0,0";
                    refr  = 0.0;
                }
            }
            else
            {
                refrbs.Text = "0,0";
                refr = 0.0;
            }

            if (BigSpherer.TextLength > 0)
            {
                if (double.TryParse(BigSpherer.Text, out x))
                {
                    if (x < 0.0)
                    {
                        BigSpherer.Text = "0,0";
                        x = 0.0;
                    }
                    else if (x > 1.0)
                    {
                        BigSpherer.Text = "1,0";
                        x = 0.0;
                    }
                }
                else
                {
                    BigSpherer.Text = "0,0";
                    x = 0.0;
                }
            }
            else
            {
                BigSpherer.Text = "0,0";
                x = 0.0;
            }

            if (BigSphereg.TextLength > 0)
            {
                if (double.TryParse(BigSphereg.Text, out y))
                {
                    if (y < 0.0)
                    {
                        BigSphereg.Text = "0,0";
                        y = 0.0;
                    }
                    else if (y > 1.0)
                    {
                        BigSphereg.Text = "1,0";
                        y = 0.0;
                    }
                }
                else
                {
                    BigSphereg.Text = "0,0";
                    y = 0.0;
                }
            }
            else
            {
                BigSphereg.Text = "0,0";
                y = 0.0;
            }

            if (BigSphereb.TextLength > 0)
            {
                if (double.TryParse(BigSphereb.Text, out z))
                {
                    if (z < 0.0)
                    {
                        BigSphereb.Text = "0,0";
                        z = 0.0;
                    }
                    else if (z > 1.0)
                    {
                        BigSphereb.Text = "1,0";
                        z = 0.0;
                    }
                }
                else
                {
                    BigSphereb.Text = "0,0";
                    z = 0.0;
                }
            }
            else
            {
                BigSphereb.Text = "0,0";
                z = 0.0;
            }
            view.SetColBigSphere((float)x, (float)y, (float)z, (float)refl, (float)refr);
            view.Update();

            glControl1.SwapBuffers();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            double x, y, z, refl, refr;
            if (reflss.TextLength > 0)
            {
                if (double.TryParse(reflss.Text, out refl))
                {
                    if (refl < 0.0)
                    {
                        reflss.Text = "0,0";
                        refl = 0.0;
                    }
                }
                else
                {
                    reflss.Text = "0,0";
                    refl = 0.0;
                }
            }
            else
            {
                reflss.Text = "0,0";
                refl = 0.0;
            }

            if (refrss.TextLength > 0)
            {
                if (double.TryParse(refrss.Text, out refr))
                {
                    if (refr < 0.0)
                    {
                        refrss.Text = "0,0";
                        refr = 0.0;
                    }
                }
                else
                {
                    refrss.Text = "0,0";
                    refr = 0.0;
                }
            }
            else
            {
                refrss.Text = "0,0";
                refr = 0.0;
            }

            if (SmallSpherer.TextLength > 0)
            {
                if (double.TryParse(SmallSpherer.Text, out x))
                {
                    if (x < 0.0)
                    {
                        SmallSpherer.Text = "0,0";
                        x = 0.0;
                    }
                    else if (x > 1.0)
                    {
                        SmallSpherer.Text = "1,0";
                        x = 0.0;
                    }
                }
                else
                {
                    SmallSpherer.Text = "0,0";
                    x = 0.0;
                }
            }
            else
            {
                SmallSpherer.Text = "0,0";
                x = 0.0;
            }

            if (SmallSphereg.TextLength > 0)
            {
                if (double.TryParse(SmallSphereg.Text, out y))
                {
                    if (y < 0.0)
                    {
                        SmallSphereg.Text = "0,0";
                        y = 0.0;
                    }
                    else if (y > 1.0)
                    {
                        SmallSphereg.Text = "1,0";
                        y = 0.0;
                    }
                }
                else
                {
                    SmallSphereg.Text = "0,0";
                    y = 0.0;
                }
            }
            else
            {
                SmallSphereg.Text = "0,0";
                y = 0.0;
            }

            if (SmallSphereb.TextLength > 0)
            {
                if (double.TryParse(SmallSphereb.Text, out z))
                {
                    if (z < 0.0)
                    {
                        SmallSphereb.Text = "0,0";
                        z = 0.0;
                    }
                    else if (z > 1.0)
                    {
                        SmallSphereb.Text = "1,0";
                        z = 0.0;
                    }
                }
                else
                {
                    SmallSphereb.Text = "0,0";
                    z = 0.0;
                }
            }
            else
            {
                SmallSphereb.Text = "0,0";
                z = 0.0;
            }
            view.SetColSmallSphere((float)x, (float)y, (float)z, (float)refl, (float)refr);
            view.Update();

            glControl1.SwapBuffers();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            double x, y, z, refl, refr;
            if (reflt.TextLength > 0)
            {
                if (double.TryParse(reflt.Text, out refl))
                {
                    if (refl < 0.0)
                    {
                        reflt.Text = "0,0";
                        refl = 0.0;
                    }
                }
                else
                {
                    reflt.Text = "0,0";
                    refl = 0.0;
                }
            }
            else
            {
                reflt.Text = "0,0";
                refl = 0.0;
            }

            if (refrt.TextLength > 0)
            {
                if (double.TryParse(refrt.Text, out refr))
                {
                    if (refr < 0.0)
                    {
                        refrt.Text = "0,0";
                        refr = 0.0;
                    }
                }
                else
                {
                    refrt.Text = "0,0";
                    refr = 0.0;
                }
            }
            else
            {
                refrt.Text = "0,0";
                refr = 0.0;
            }

            if (Thetrr.TextLength > 0)
            {
                if (double.TryParse(Thetrr.Text, out x))
                {
                    if (x < 0.0)
                    {
                        Thetrr.Text = "0,0";
                        x = 0.0;
                    }
                    else if (x > 1.0)
                    {
                        Thetrr.Text = "1,0";
                        x = 0.0;
                    }
                }
                else
                {
                    Thetrr.Text = "0,0";
                    x = 0.0;
                }
            }
            else
            {
                Thetrr.Text = "0,0";
                x = 0.0;
            }

            if (Thetrg.TextLength > 0)
            {
                if (double.TryParse(Thetrg.Text, out y))
                {
                    if (y < 0.0)
                    {
                        Thetrg.Text = "0,0";
                        y = 0.0;
                    }
                    else if (y > 1.0)
                    {
                        Thetrg.Text = "1,0";
                        y = 0.0;
                    }
                }
                else
                {
                    Thetrg.Text = "0,0";
                    y = 0.0;
                }
            }
            else
            {
                Thetrg.Text = "0,0";
                y = 0.0;
            }

            if (Thetrb.TextLength > 0)
            {
                if (double.TryParse(Thetrb.Text, out z))
                {
                    if (z < 0.0)
                    {
                        Thetrb.Text = "0,0";
                        z = 0.0;
                    }
                    else if (z > 1.0)
                    {
                        Thetrb.Text = "1,0";
                        z = 0.0;
                    }
                }
                else
                {
                    Thetrb.Text = "0,0";
                    z = 0.0;
                }
            }
            else
            {
                Thetrb.Text = "0,0";
                z = 0.0;
            }
            view.SetColThetr((float)x, (float)y, (float)z, (float)refl, (float)refr);
            view.Update();

            glControl1.SwapBuffers();
        }

        private void radioButton17_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked)
            {
                view.SendLeftRight(1);
                view.Update();

                glControl1.SwapBuffers();
            }
        }

        private void radioButton18_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked)
            {
                view.SendLeftRight(2);
                view.Update();

                glControl1.SwapBuffers();
            }
        }

        private void radioButton20_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked)
            {
                view.SendTopDown(1);
                view.Update();

                glControl1.SwapBuffers();
            }
        }

        private void radioButton19_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked)
            {
                view.SendTopDown(2);
                view.Update();

                glControl1.SwapBuffers();
            }
        }

        private void radioButton21_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked)
            {
                view.SendFrontBack(2);
                view.Update();

                glControl1.SwapBuffers();
            }
        }

        private void radioButton22_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked)
            {
                view.SendFrontBack(1);
                view.Update();

                glControl1.SwapBuffers();
            }
        }
    }
}
