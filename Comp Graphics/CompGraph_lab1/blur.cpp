#include "blur.h"

BlurFilter::BlurFilter(const QPixmap& pix, int _sizeX, int _sizeY) : MatrixFilter(pix)
{
    SizeX = _sizeX;
    SizeY = _sizeY;

    kernel = new float* [SizeX];
    kernel[0] = new float[SizeX * SizeY];
    for (int i = 1; i != SizeX; ++i)
    {
        kernel[i] = kernel[i - 1] + SizeY;
    }
    for(int i = 0; i != SizeX; ++i)
        for(int j = 0; j != SizeY; ++j)
            kernel[i][j] = static_cast<float>(1.0F / (static_cast<float>(SizeX * SizeY)));
}
