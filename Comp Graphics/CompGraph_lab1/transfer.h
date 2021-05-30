#ifndef TRANSFERFILTER_H
#define TRANSFERFILTER_H

#include "FilterLibrary.h"

class TransferFilter : public Filter
{
protected:
    QColor CalculNewColor(pixel _point);
public:
    TransferFilter(const QPixmap& pix);
};

#endif // TRANSFERFILTER_H
