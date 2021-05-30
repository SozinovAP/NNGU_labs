#include "sobel.h"

SobelFilter::SobelFilter(const QPixmap& pix, char mode) : MatrixFilter(pix)
{
    SizeX = 3;
    SizeY = 3;
    kernel = new float* [SizeX];
    kernel[0] = new float[SizeX * SizeY];
    for (int i = 1; i != SizeX; ++i)
    {
        kernel[i] = kernel[i - 1] + SizeY;
    }
    if (mode == 'x')
    {
        kernel[0][0] = -1;
        kernel[0][1] = 0;
        kernel[0][2] = 1;
        kernel[1][0] = -2;
        kernel[1][1] = 0;
        kernel[1][2] = 2;
        kernel[2][0] = -1;
        kernel[2][1] = 0;
        kernel[2][2] = 1;
    }
    else if (mode == 'y')
    {
        kernel[0][0] = -1;
        kernel[0][1] = -2;
        kernel[0][2] = -1;
        kernel[1][0] = 0;
        kernel[1][1] = 0;
        kernel[1][2] = 0;
        kernel[2][0] = 1;
        kernel[2][1] = 2;
        kernel[2][2] = 1;
    }
}
