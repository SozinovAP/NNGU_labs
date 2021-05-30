#ifndef MIRRORFILTER_H
#define MIRRORFILTER_H

#include "FilterLibrary.h"

class GlassFilter : public Filter
{
protected:
    QColor CalculNewColor(pixel _point);
public:
    GlassFilter(QPixmap pix);
};

#endif // MIRRORFILTER_H
