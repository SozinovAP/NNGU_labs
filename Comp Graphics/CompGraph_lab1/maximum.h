#ifndef MAXIMUMFILTER_H
#define MAXIMUMFILTER_H

#include "FilterLibrary.h"

class MaximumFilter : public MatrixFilter
{
protected:
    QColor CalculNewColor(pixel _point);
public:
    MaximumFilter(const QPixmap& pix);
};

#endif // MAXIMUMFILTER_H
