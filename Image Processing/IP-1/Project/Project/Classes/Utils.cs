using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace IP1
{
    namespace Imaging
    {
        public static class Utils
        {
            public static float Clamp(float value, float min, float max)
            {
                if (min > max)
                    throw new Exception("Clamp error min>max");

                if (value < min)
                    return min;
                if (value > max)
                    return max;
                return value;
            }

            

            public static BitmapSource ImageToBitmapSource(IP1.Imaging.Image image)
            {
                System.Windows.Media.PixelFormat pf = PixelFormats.Bgr24;
                int width = image.Width;
                int height = image.Height;
                int rawStride = (width * pf.BitsPerPixel + 7) / 8;
                byte[] rawImage = image.GetBytesBGR24().ToArray();

                return BitmapSource.Create(width, height,
                    96, 96, pf, null,
                    rawImage, rawStride);
            }


            public static IEnumerable<byte> GetBytesBGR24(System.Drawing.Image image)
            {
                /*using (var ms = new MemoryStream())
                {
                    image.Save(ms, image.RawFormat);
                    return ms.ToArray();
                }*/
                ImageConverter imgCon = new ImageConverter();
                return (byte[])imgCon.ConvertTo(image, typeof(byte[]));
            }

            public static BitmapImage ImageToBitmapSource(System.Drawing.Image image)
            {
                var memory = new MemoryStream();
                image.Save(memory, System.Drawing.Imaging.ImageFormat.Png);
                memory.Position = 0;

                var bitmapImage = new BitmapImage();
                bitmapImage.BeginInit();
                bitmapImage.StreamSource = memory;
                bitmapImage.CacheOption = BitmapCacheOption.OnLoad;
                bitmapImage.EndInit();
                return bitmapImage;
            }
        }
    }
}
