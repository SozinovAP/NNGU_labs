namespace CompGraph_lab2
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.glControl1 = new OpenTK.GLControl();
            this.button3 = new System.Windows.Forms.Button();
            this.LayerTomo = new System.Windows.Forms.TrackBar();
            this.QuadsV = new System.Windows.Forms.RadioButton();
            this.TextureV = new System.Windows.Forms.RadioButton();
            this.TrackBar_minTF = new System.Windows.Forms.TrackBar();
            this.TrackBar_WidthTF = new System.Windows.Forms.TrackBar();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.Table = new System.Windows.Forms.TableLayoutPanel();
            ((System.ComponentModel.ISupportInitialize)(this.LayerTomo)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TrackBar_minTF)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.TrackBar_WidthTF)).BeginInit();
            this.Table.SuspendLayout();
            this.SuspendLayout();
            // 
            // glControl1
            // 
            this.glControl1.BackColor = System.Drawing.Color.Black;
            this.Table.SetColumnSpan(this.glControl1, 2);
            this.glControl1.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.glControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.glControl1.Location = new System.Drawing.Point(120, 51);
            this.glControl1.Name = "glControl1";
            this.glControl1.Size = new System.Drawing.Size(540, 415);
            this.glControl1.TabIndex = 0;
            this.glControl1.VSync = false;
            this.glControl1.Load += new System.EventHandler(this.glControl1_Load);
            this.glControl1.Paint += new System.Windows.Forms.PaintEventHandler(this.glControl1_Paint);
            this.glControl1.Resize += new System.EventHandler(this.glControl1_Resize);
            // 
            // button3
            // 
            this.Table.SetColumnSpan(this.button3, 2);
            this.button3.Location = new System.Drawing.Point(550, 532);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(151, 21);
            this.button3.TabIndex = 3;
            this.button3.Text = "Загрузить томограмму";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // LayerTomo
            // 
            this.Table.SetColumnSpan(this.LayerTomo, 3);
            this.LayerTomo.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.LayerTomo.Location = new System.Drawing.Point(3, 3);
            this.LayerTomo.Name = "LayerTomo";
            this.Table.SetRowSpan(this.LayerTomo, 2);
            this.LayerTomo.Size = new System.Drawing.Size(658, 42);
            this.LayerTomo.TabIndex = 4;
            this.LayerTomo.Scroll += new System.EventHandler(this.trackBar1_Scroll);
            // 
            // QuadsV
            // 
            this.QuadsV.AutoSize = true;
            this.QuadsV.Checked = true;
            this.QuadsV.Location = new System.Drawing.Point(667, 3);
            this.QuadsV.Name = "QuadsV";
            this.QuadsV.Size = new System.Drawing.Size(72, 17);
            this.QuadsV.TabIndex = 5;
            this.QuadsV.TabStop = true;
            this.QuadsV.Text = "QuadStrip";
            this.QuadsV.UseVisualStyleBackColor = true;
            // 
            // TextureV
            // 
            this.TextureV.AutoSize = true;
            this.TextureV.Location = new System.Drawing.Point(667, 27);
            this.TextureV.Name = "TextureV";
            this.TextureV.Size = new System.Drawing.Size(61, 17);
            this.TextureV.TabIndex = 6;
            this.TextureV.TabStop = true;
            this.TextureV.Text = "Texture";
            this.TextureV.UseVisualStyleBackColor = true;
            // 
            // TrackBar_minTF
            // 
            this.Table.SetColumnSpan(this.TrackBar_minTF, 2);
            this.TrackBar_minTF.Dock = System.Windows.Forms.DockStyle.Fill;
            this.TrackBar_minTF.Location = new System.Drawing.Point(3, 468);
            this.TrackBar_minTF.Maximum = 5000;
            this.TrackBar_minTF.Name = "TrackBar_minTF";
            this.TrackBar_minTF.Size = new System.Drawing.Size(541, 26);
            this.TrackBar_minTF.TabIndex = 7;
            this.TrackBar_minTF.Scroll += new System.EventHandler(this.TrackBar_minTF_Scroll);
            // 
            // TrackBar_WidthTF
            // 
            this.Table.SetColumnSpan(this.TrackBar_WidthTF, 2);
            this.TrackBar_WidthTF.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.TrackBar_WidthTF.Location = new System.Drawing.Point(3, 500);
            this.TrackBar_WidthTF.Maximum = 5000;
            this.TrackBar_WidthTF.Name = "TrackBar_WidthTF";
            this.TrackBar_WidthTF.Size = new System.Drawing.Size(541, 26);
            this.TrackBar_WidthTF.TabIndex = 8;
            this.TrackBar_WidthTF.Value = 1000;
            this.TrackBar_WidthTF.Scroll += new System.EventHandler(this.TrackBar_WidthTF_Scroll);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Dock = System.Windows.Forms.DockStyle.Right;
            this.label1.Location = new System.Drawing.Point(603, 465);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(58, 32);
            this.label1.TabIndex = 9;
            this.label1.Text = "Минимум:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Dock = System.Windows.Forms.DockStyle.Left;
            this.label2.Location = new System.Drawing.Point(667, 465);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(13, 32);
            this.label2.TabIndex = 10;
            this.label2.Text = "0";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Dock = System.Windows.Forms.DockStyle.Left;
            this.label3.Location = new System.Drawing.Point(667, 497);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(31, 32);
            this.label3.TabIndex = 12;
            this.label3.Text = "1000";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Dock = System.Windows.Forms.DockStyle.Right;
            this.label4.Location = new System.Drawing.Point(615, 497);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(46, 32);
            this.label4.TabIndex = 11;
            this.label4.Text = "Ширина";
            // 
            // Table
            // 
            this.Table.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Table.ColumnCount = 4;
            this.Table.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 15F));
            this.Table.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 55F));
            this.Table.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 15F));
            this.Table.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 15F));
            this.Table.Controls.Add(this.LayerTomo, 0, 0);
            this.Table.Controls.Add(this.glControl1, 1, 2);
            this.Table.Controls.Add(this.button3, 2, 5);
            this.Table.Controls.Add(this.label2, 3, 3);
            this.Table.Controls.Add(this.QuadsV, 3, 0);
            this.Table.Controls.Add(this.label4, 2, 4);
            this.Table.Controls.Add(this.TextureV, 3, 1);
            this.Table.Controls.Add(this.TrackBar_minTF, 0, 3);
            this.Table.Controls.Add(this.label1, 2, 3);
            this.Table.Controls.Add(this.TrackBar_WidthTF, 0, 4);
            this.Table.Controls.Add(this.label3, 3, 4);
            this.Table.Location = new System.Drawing.Point(3, 3);
            this.Table.Name = "Table";
            this.Table.RowCount = 6;
            this.Table.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24F));
            this.Table.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24F));
            this.Table.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.Table.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 32F));
            this.Table.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 32F));
            this.Table.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 29F));
            this.Table.Size = new System.Drawing.Size(782, 558);
            this.Table.TabIndex = 13;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(784, 561);
            this.Controls.Add(this.Table);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.Resize += new System.EventHandler(this.Form1_Resize);
            ((System.ComponentModel.ISupportInitialize)(this.LayerTomo)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TrackBar_minTF)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.TrackBar_WidthTF)).EndInit();
            this.Table.ResumeLayout(false);
            this.Table.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private OpenTK.GLControl glControl1;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.TrackBar LayerTomo;
        private System.Windows.Forms.RadioButton QuadsV;
        private System.Windows.Forms.RadioButton TextureV;
        private System.Windows.Forms.TrackBar TrackBar_minTF;
        private System.Windows.Forms.TrackBar TrackBar_WidthTF;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TableLayoutPanel Table;
    }
}

