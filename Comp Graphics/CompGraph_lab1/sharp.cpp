#include "sharp.h"

SharpFilter::SharpFilter(const QPixmap& pix) : MatrixFilter(pix)
{
    SizeX = 3;
    SizeY = 3;
    kernel = new float* [SizeX];
    kernel[0] = new float[SizeX * SizeY];
    for (int i = 1; i != SizeX; ++i)
    {
        kernel[i] = kernel[i - 1] + SizeY;
    }
    kernel[0][0] = 0;
    kernel[0][1] = -1;
    kernel[0][2] = 0;
    kernel[1][0] = -1;
    kernel[1][1] = 5;
    kernel[1][2] = -1;
    kernel[2][0] = 0;
    kernel[2][1] = -1;
    kernel[2][2] = 0;
}
