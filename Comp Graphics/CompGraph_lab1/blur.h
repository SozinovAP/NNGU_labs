#ifndef BLURFILTER_H
#define BLURFILTER_H

#include "FilterLibrary.h"

class BlurFilter : public MatrixFilter
{
public:
    BlurFilter(const QPixmap& pix, int _sizeX = 3, int _sizeY = 3);
};

#endif // BLURFILTER_H
