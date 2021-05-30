#include "sepia.h"

QColor SepiaFilter::CalculNewColor(pixel _point)
{
    QColor _col = resimg.pixel(_point.x, _point.y);
    int k = 100;
    double col = _col.red() * 0.299 + _col.green() * 0.587 + _col.blue() * 0.114;
    return QColor::fromRgb(Clamp(static_cast<int>(col + 2 * k), 0, 255), Clamp(static_cast<int>(col + 0.5 * k), 0, 255), Clamp(static_cast<int>(col - 1 * k), 0, 255));
}

SepiaFilter::SepiaFilter(const QPixmap& pix) : Filter(pix)
{

}
