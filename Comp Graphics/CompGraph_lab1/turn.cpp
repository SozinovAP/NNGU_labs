#include "turn.h"

QColor TurnFilter::CalculNewColor(pixel _point)
{
    double angle = 0.2;
    int x0 = resimg.width() / 2;
    int y0 = resimg.height() / 2;
    int x = static_cast<int>((_point.x - x0) * cos(angle) - (_point.y - y0) * sin(angle) + x0);
    int y = static_cast<int>((_point.x - x0) * sin(angle) + (_point.y - y0) * cos(angle) + y0);
    return resimg.pixel(Clamp(x, 0, resimg.width() - 1), Clamp(y, 0, resimg.height() - 1));
}

TurnFilter::TurnFilter(const QPixmap& pix) : Filter(pix)
{

}
