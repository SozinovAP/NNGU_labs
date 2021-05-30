using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using OpenCvSharp;
using OpenCvSharp.Extensions;

namespace IP1
{
    class ConvertOpenCV
    {
        private static Image nullptr;

        //convert Ip1.Imaging.Image to Mat
        public static Mat ImageToMat(IP1.Imaging.Image img)
        {
            Bitmap bmp = new Bitmap(img.Width, img.Height);
            for (int y = 0; y < bmp.Height; ++y)
            {
                for (int x = 0; x < bmp.Width; ++x)
                {
                    bmp.SetPixel(x, y, System.Drawing.Color.FromArgb(img[y, x].r, img[y, x].g, img[y, x].b));
                }
            }

            return bmp.ToMat();
        }

        //Convert to grayscale
        public static System.Drawing.Image ConvertToGray(IP1.Imaging.Image img)
        {
            Mat MatImage = ImageToMat(img); //convert IP1.Imaging.Image to Mat

            DateTime StartTime = DateTime.Now;
            Mat imageGray = MatImage.CvtColor(ColorConversionCodes.RGB2GRAY);

            DateTime EndTime = DateTime.Now;
            MainWindow.TimeOpenCvWork = EndTime.Subtract(StartTime).TotalSeconds;
            return imageGray.ToBitmap();
        }

        //Convert from RGB to HSV
        public static System.Drawing.Image RGB2HSV(IP1.Imaging.Image img)
        {
            try
            {
                Mat MatImage = ImageToMat(img);//convert IP1.Imaging.Image to Mat

                DateTime StartTime = DateTime.Now;
            
                Mat imageHSV = MatImage.CvtColor(ColorConversionCodes.RGB2HSV);

                DateTime EndTime = DateTime.Now;
                MainWindow.TimeOpenCvWork = EndTime.Subtract(StartTime).TotalSeconds;

                return imageHSV.ToBitmap();
            }
            catch (OpenCVException e)
            {
                MessageBox.Show("Изображение не в RGB представлении");
            }
            return nullptr;
        }

        //Convert HSV to RGB
        public static System.Drawing.Image HSV2RGB(IP1.Imaging.Image img)
        {
            try
            {
                Mat MatImage = ImageToMat(img);//convert IP1.Imaging.Image to Mat

                DateTime StartTime = DateTime.Now;
                Mat imageRGB = MatImage.CvtColor(ColorConversionCodes.HSV2RGB);
                DateTime EndTime = DateTime.Now;
                MainWindow.TimeOpenCvWork = EndTime.Subtract(StartTime).TotalSeconds;

                return imageRGB.ToBitmap();
            }
            catch (OpenCVException e)
            {
                MessageBox.Show("Изображение не в HSV представлении");
            }
            return nullptr;
        }
    }
}
