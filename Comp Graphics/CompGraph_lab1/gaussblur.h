#ifndef GAUSSBLURFILTER_H
#define GAUSSBLURFILTER_H

#include "FilterLibrary.h"

class GaussBlurFilter : public MatrixFilter
{
public:
    GaussBlurFilter(const QPixmap& pix);
    void GaussKernel(int radius, float sigma);
};

#endif // GAUSSBLURFILTER_H
