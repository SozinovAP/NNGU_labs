#ifndef GRAYWORLDFILTER_H
#define GRAYWORLDFILTER_H

#include "FilterLibrary.h"

class GrayWorldFilter : public Filter
{
private:
    int sumR, sumG, sumB;
    double Average;
    void SumColor();
protected:
    QColor CalculNewColor(pixel _point);
public:
    GrayWorldFilter(const QPixmap& pix);
    void ProcImg();

};

#endif // GRAYWORLDFILTER_H
