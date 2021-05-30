#ifndef BRIGHTNESSFILTER_H
#define BRIGHTNESSFILTER_H

#include "FilterLibrary.h"

class BrightnessFilter : public Filter
{
protected:
    QColor CalculNewColor(pixel _point);
public:
    BrightnessFilter(const QPixmap& pix);
};

#endif // BRIGHTNESSFILTER_H
