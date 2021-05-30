#include "blackwhite.h"

QColor BlackWhiteFilter::CalculNewColor(pixel _point)
{
    QColor _col = resimg.pixel(_point.x, _point.y);
    double col = _col.red() * 0.299 + _col.green() * 0.587 + _col.blue() * 0.114;
    return QColor::fromRgb(static_cast<int>(col), static_cast<int>(col), static_cast<int>(col));
}

BlackWhiteFilter::BlackWhiteFilter(const QPixmap& pix) : Filter(pix)
{
}
