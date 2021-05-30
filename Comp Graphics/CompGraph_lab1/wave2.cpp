#include "wave2.h"

QColor Wave2Filter::CalculNewColor(pixel _point)
{
    int x = static_cast<int>(_point.x + 20 * sin(2 * M_PI * _point.y / 30));
    int y = _point.y;
    return resimg.pixel(Clamp(x, 0, resimg.width() - 1), Clamp(y, 0, resimg.height() - 1));
}

Wave2Filter::Wave2Filter(const QPixmap& pix) : Filter(pix)
{

}
