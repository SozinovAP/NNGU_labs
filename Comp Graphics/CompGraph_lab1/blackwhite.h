#ifndef BLACKWHITEFILTER_H
#define BLACKWHITEFILTER_H

#include "FilterLibrary.h"

class BlackWhiteFilter : public Filter
{
protected:
   QColor CalculNewColor(pixel _point);
public:
    BlackWhiteFilter(const QPixmap& pix);
};

#endif // BLACKWHITEFILTER_H
