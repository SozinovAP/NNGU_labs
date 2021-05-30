#include "grayword.h"

QColor GrayWorldFilter::CalculNewColor(pixel _point)
{
    QColor _col = resimg.pixel(_point.x, _point.y);
    return QColor::fromRgb(Clamp(static_cast<int>(_col.red() * Average / sumR), 0, 255),
                        Clamp(static_cast<int>(_col.green() * Average / sumG), 0, 255),
                        Clamp(static_cast<int>(_col.blue() * Average / sumB), 0, 255));
}

GrayWorldFilter::GrayWorldFilter(const QPixmap& pix) : Filter(pix)
{
    sumR = 0;
    sumG = 0;
    sumB = 0;
    Average = 0;
}

void GrayWorldFilter::ProcImg()
{
    QImage resPix = workimg.toImage();
    resimg = resPix;

    SumColor();

    QPainter p(&resPix);
    for (point.x = 0; point.x < resPix.width(); ++point.x)
    {
        for (point.y = 0; ((F) &&  point.y < resPix.height()); ++point.y)
        {
            QColor color = CalculNewColor(point);
            p.setPen(color);
            p.drawPoint(point.x, point.y);
        }
        emit process(100 * point.x / (resPix.width() - 1));
    }

    if (F)
    {
        workimg = QPixmap::fromImage(resPix);
    }
    result(workimg);
    finished();
}

void GrayWorldFilter::SumColor()
{
    int N = resimg.width() * resimg.height();
    for (point.x = 0; point.x < resimg.width(); ++point.x)
    {
        for (point.y = 0; point.y < resimg.height(); ++point.y)
        {
            QColor col = resimg.pixel(point.x, point.y);
            sumR += col.red();
            sumG += col.green();
            sumB += col.blue();
        }
    }
    sumR /= N;
    sumG /= N;
    sumB /= N;
    Average = (sumR + sumB + sumG) / 3.0;
}

