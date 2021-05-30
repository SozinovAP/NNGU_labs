using IP1.Imaging;
using IP1.Imaging.Filters;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace IP1
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public static Imaging.Image myImage;
        public static Imaging.Image CustomImage;
        public static System.Drawing.Image openCVImage;
        public static double TimeOpenCvWork;

        public MainWindow()
        {

            InitializeComponent();
            RenderOptions.SetBitmapScalingMode(CustomIm, BitmapScalingMode.NearestNeighbor);
            RenderOptions.SetBitmapScalingMode(OpenCVIm, BitmapScalingMode.NearestNeighbor);
            RenderOptions.SetBitmapScalingMode(OriginalIm, BitmapScalingMode.NearestNeighbor);

            /*Imaging.Image myImage = Imaging.Image.Load("image");

            //myImage = new FilterGrayScale(FilterGrayScale.GrayScaleType.Gimp).Run(myImage);

            ConvertOpenCV opcv = new ConvertOpenCV();
            System.Drawing.Image SecondIm = opcv.ConvertToGray(Imaging.Image.Load("image"));


            image2.Source = Utils.ImageToBitmapSource(myImage);
            
            var memory = new MemoryStream();
                SecondIm.Save(memory, ImageFormat.Png);
                memory.Position = 0;

                var bitmapImage = new BitmapImage();
                bitmapImage.BeginInit();
                bitmapImage.StreamSource = memory;
                bitmapImage.CacheOption = BitmapCacheOption.OnLoad;
                bitmapImage.EndInit();
            image.Source = bitmapImage;

            CustomIm.Source = Utils.ImageToBitmapSource(myImage);
            System.Drawing.Image three = opcv.RGB2HSV(Imaging.Image.Load("image"));

            var memory = new MemoryStream();
            three.Save(memory, ImageFormat.Png);
            memory.Position = 0;

            var bitmapImage = new BitmapImage();
            bitmapImage.BeginInit();
            bitmapImage.StreamSource = memory;
            bitmapImage.CacheOption = BitmapCacheOption.OnLoad;
            bitmapImage.EndInit();
            OpenCVIm.Source = bitmapImage;*/
        }

        private void ButtonLoadImage_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();

            dlg.DefaultExt = ".png";
            dlg.Filter = "JPEG Files (*.jpeg)|*.jpeg|PNG Files (*.png)|*.png|JPG Files (*.jpg)|*.jpg";
            Nullable<bool> result = dlg.ShowDialog();

            if (result == true)
            {
                string filename = dlg.FileName;
                //MainWindow.myImage = Imaging.Image.Load(filename);!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                MainWindow.myImage = Imaging.Image.Load("image");   //!!!!!!!!!!!!!!!!!!!!!!
                OriginalIm.Source = Utils.ImageToBitmapSource(myImage);
            }
        }

        public void Clear() 
        {
            TimeCustomlabel.Content = "";
            TimeOpenCVlabel.Content = "";
            Qualitylabel.Content = "";
        }
        public void RunConvertToGrayScale()
        {
            Clear(); //Clear labels
            DateTime StartTime;
            DateTime EndTime;
            StartTime = DateTime.Now;
            //Custom convert to grayscale
            MainWindow.CustomImage = new FilterGrayScale(FilterGrayScale.GrayScaleType.Gimp).Run(myImage);
            
            EndTime = DateTime.Now;
            //Set time
            TimeCustomlabel.Content = EndTime.Subtract(StartTime).TotalSeconds;
            //load result last convert on Form
            CustomIm.Source = Utils.ImageToBitmapSource(CustomImage);

            //OpenCV convert to grayscale
            MainWindow.openCVImage = ConvertOpenCV.ConvertToGray(myImage);

            //Set time 
            TimeOpenCVlabel.Content = TimeOpenCvWork;

            //load result last convert on Form
            OpenCVIm.Source = Utils.ImageToBitmapSource(openCVImage);
            Metrics mt = new Metrics();

            //Set result compare
            Qualitylabel.Content = mt.CompareImage(openCVImage, CustomImage);
        }

        public void RunConvertRGBToHSV()
        {
            Clear(); //Clear labels
            DateTime StartTime;
            DateTime EndTime;
            StartTime = DateTime.Now;

            //Custom convert RGB to HSV
            //Заменить на перевод в HSV
            MainWindow.CustomImage = new FilterGrayScale(FilterGrayScale.GrayScaleType.Gimp).Run(myImage);
            
            EndTime = DateTime.Now;
            //Set time
            TimeCustomlabel.Content = EndTime.Subtract(StartTime).TotalSeconds;
            //load result last convert on Form
            CustomIm.Source = Utils.ImageToBitmapSource(CustomImage);

            //OpenCV convert RGB to HSV
            MainWindow.openCVImage = ConvertOpenCV.RGB2HSV(myImage);

            //Set time 
            TimeOpenCVlabel.Content = TimeOpenCvWork;

            //load result last convert on Form
            OpenCVIm.Source = Utils.ImageToBitmapSource(openCVImage);
            Metrics mt = new Metrics();

            //Set result compare
            Qualitylabel.Content = mt.CompareImage(openCVImage, CustomImage);
        }

        public void RunConvertHSVToRGB()
        {
            Clear(); //Clear labels
            DateTime StartTime;
            DateTime EndTime;
            StartTime = DateTime.Now;

            //Custom convert HSV to RGB
            //Заменить на перевод в RGB
            MainWindow.CustomImage = new FilterGrayScale(FilterGrayScale.GrayScaleType.Gimp).Run(myImage);

            EndTime = DateTime.Now;
            //Set time
            TimeCustomlabel.Content = EndTime.Subtract(StartTime).TotalSeconds;
            //load result last convert on Form
            CustomIm.Source = Utils.ImageToBitmapSource(CustomImage);

            //OpenCV convert HSV to RGB
            MainWindow.openCVImage = ConvertOpenCV.HSV2RGB(myImage);

            //Set time 
            TimeOpenCVlabel.Content = TimeOpenCvWork;

            //load result last convert on Form
            OpenCVIm.Source = Utils.ImageToBitmapSource(openCVImage);
            Metrics mt = new Metrics();

            //Set result compare
            Qualitylabel.Content = mt.CompareImage(openCVImage, CustomImage);
        }

        private void Convert_Click(object sender, RoutedEventArgs e)
        {
            if (radioButtonGrayScale.IsChecked == true)
            {
                RunConvertToGrayScale();
            }
            else if (radioButtonRGB2HSV.IsChecked == true)
            {
                RunConvertRGBToHSV();
            }
            else if (radioButtonHSV2RGB.IsChecked == true)
            {
                RunConvertHSVToRGB();
            }
        }
    }
}
