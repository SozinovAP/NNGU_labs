#include "brightness.h"

QColor BrightnessFilter::CalculNewColor(pixel _point)
{
    QColor _col = resimg.pixel(_point.x, _point.y);
    int k = 80;
    return QColor::fromRgb(Clamp(_col.red() + k, 0, 255), Clamp(_col.green() + k, 0, 255), Clamp(_col.blue() + k, 0, 255));
}

BrightnessFilter::BrightnessFilter(const QPixmap& pix) : Filter(pix)
{

}
