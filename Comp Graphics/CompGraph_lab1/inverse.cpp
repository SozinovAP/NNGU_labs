#include "inverse.h"

QColor InverseFilter::CalculNewColor(pixel _point)
{
    QColor _col = resimg.pixel(_point.x, _point.y);
    return QColor::fromRgb(255 - _col.red(), 255 - _col.green(), 255 - _col.blue());
}

InverseFilter::InverseFilter(const QPixmap& pix) : Filter(pix)
{
}
