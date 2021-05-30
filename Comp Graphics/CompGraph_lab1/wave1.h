#ifndef WAVEFILTER_H
#define WAVEFILTER_H

#include "FilterLibrary.h"

class Wave1Filter : public Filter
{
protected:
    QColor CalculNewColor(pixel _point);
public:
    Wave1Filter(const QPixmap& pix);
};

#endif // WAVEFILTER_H
