#ifndef SHARPFILTER_H
#define SHARPFILTER_H

#include "FilterLibrary.h"

class SharpFilter : public MatrixFilter
{
public:
    SharpFilter(const QPixmap& pix);
};

#endif // SHARPFILTER_H
