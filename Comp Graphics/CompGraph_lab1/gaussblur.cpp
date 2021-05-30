#include "gaussblur.h"
 #include <cmath> 
GaussBlurFilter::GaussBlurFilter(const QPixmap& pix) : MatrixFilter(pix)
{
    GaussKernel(3, 2);
}

void GaussBlurFilter::GaussKernel(int radius, float sigma)
{
    //размер ядра
    int size = radius * 2 + 1;
    SizeX = size;
    SizeY = size;
    //создание ядра
    kernel = new float* [size];
    kernel[0] = new float[size * size];
    for (int i = 1; i != size; ++i)
    {
        kernel[i] = kernel[i - 1] + size;
    }
    //коэффициент нормировки
    float norm = 0;
    //рассчитываем ядро
    for (int i = -radius; i <= radius; ++i)
        for (int j = -radius; j <= radius; ++j)
        {
            kernel[i + radius][j + radius] = static_cast<float>(std::exp(-(i * i + j * j) / (2 * sigma * sigma)));
            norm += kernel[i + radius][j + radius];
        }
    //нормировка ядра
    for (int i = 0; i != size; ++i)
        for (int j = 0; j != size; ++j)
            kernel[i][j] /= norm;
}
