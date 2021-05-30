#ifndef AUTOLEVELFILTER_H
#define AUTOLEVELFILTER_H

#include "FilterLibrary.h"

class AutoLevelFilter : public Filter
{
private:
    int maxR, maxG, maxB;
    int minR, minG, minB;
    void MaxMin();
protected:
    QColor CalculNewColor(pixel _point);
public:
    AutoLevelFilter(const QPixmap& pix);
    void ProcImg();
};

#endif // AUTOLEVELFILTER_H
