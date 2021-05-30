#ifndef TURNFILTER_H
#define TURNFILTER_H

#include "FilterLibrary.h"

class TurnFilter : public Filter
{
protected:
    QColor CalculNewColor(pixel _point);
public:
    TurnFilter(const QPixmap& pix);
};

#endif // TURNFILTER_H
