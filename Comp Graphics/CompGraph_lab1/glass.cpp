#include "glass.h"

QColor GlassFilter::CalculNewColor(pixel _point)
{
    srand(time_t(0));
    return resimg.pixel(Clamp(_point.x + static_cast<int>((static_cast<double>(rand()) / RAND_MAX - 0.5) * 10), 0, resimg.width()),
                        Clamp(_point.y + static_cast<int>((static_cast<double>(rand()) / RAND_MAX - 0.5) * 10), 0, resimg.height()));
}

GlassFilter::GlassFilter(QPixmap pix) : Filter(pix)
{

}
