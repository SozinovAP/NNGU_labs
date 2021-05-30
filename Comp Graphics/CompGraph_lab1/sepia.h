#ifndef SEPIAFILTER_H
#define SEPIAFILTER_H

#include "FilterLibrary.h"

class SepiaFilter : public Filter
{
protected:
    QColor CalculNewColor(pixel _point);
public:
    SepiaFilter(const QPixmap& pix);
};

#endif // SEPIAFILTER_H
