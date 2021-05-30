#ifndef EMBOSSFILTER_H
#define EMBOSSFILTER_H

#include "FilterLibrary.h"

class EmbossFilter : public MatrixFilter
{
protected:
    QColor CalculNewColor(pixel _point);
public:
    EmbossFilter(const QPixmap& pix);
    void ProcImg();

};

#endif // EMBOSSFILTER_H
