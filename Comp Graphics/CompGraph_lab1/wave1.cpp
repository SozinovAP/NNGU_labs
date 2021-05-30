#include "wave1.h"

QColor Wave1Filter::CalculNewColor(pixel _point)
{
    int x = static_cast<int>(_point.x + 20 * sin(2 * M_PI * _point.x / 60));
    int y = _point.y;
    return resimg.pixel(Clamp(x, 0, resimg.width() - 1), Clamp(y, 0, resimg.height() - 1));
}

Wave1Filter::Wave1Filter(const QPixmap& pix) : Filter(pix)
{

}
