#ifndef MEDIANFILTER_H
#define MEDIANFILTER_H

#include "FilterLibrary.h"

class MedianFilter : public MatrixFilter
{
protected:
    QColor CalculNewColor(pixel _point);
public:
    MedianFilter(const QPixmap& pix);
};

#endif // MEDIANFILTER_H
