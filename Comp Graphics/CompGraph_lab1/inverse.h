#ifndef INVERSE_H
#define INVERSE_H

#include "FilterLibrary.h"

class InverseFilter : public Filter
{
protected:
    QColor CalculNewColor(pixel _point);
public:
    InverseFilter(const QPixmap& pix);
signals:
    void process(double);
};

#endif // INVERSE_H
