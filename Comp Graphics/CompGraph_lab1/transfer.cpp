#include "transfer.h"

QColor TransferFilter::CalculNewColor(pixel _point)
{
    return resimg.pixel(Clamp(_point.x + 50, 0, resimg.width() - 1), _point.y);
}

TransferFilter::TransferFilter(const QPixmap& pix) : Filter(pix)
{

}
