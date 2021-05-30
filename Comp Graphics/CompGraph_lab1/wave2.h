#ifndef WAVEYFILTER_H
#define WAVEYFILTER_H

#include "FilterLibrary.h"

class Wave2Filter : public Filter
{
protected:
    QColor CalculNewColor(pixel _point);
public:
    Wave2Filter(const QPixmap& pix);
};

#endif // WAVEYFILTER_H
