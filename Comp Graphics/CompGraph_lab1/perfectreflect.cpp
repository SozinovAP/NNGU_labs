#include "perfectreflect.h"

QColor PerfectReflectFilter::CalculNewColor(pixel _point)
{
    QColor col = resimg.pixel(_point.x, _point.y);

    return QColor::fromRgb(Clamp(static_cast<int>(col.red() * 255 / maxR), 0, 255),
                       Clamp(static_cast<int>(col.green() * 255 / maxG), 0, 255),
                       Clamp(static_cast<int>(col.blue() * 255 / maxB), 0, 255));
}

PerfectReflectFilter::PerfectReflectFilter(QPixmap pix) : Filter(pix)
{
    maxR = 1;
    maxG = 1;
    maxB = 1;
}

void PerfectReflectFilter::ProcImg()
{
    QImage resPix = workimg.toImage();
    resimg = resPix;

    FindMax();

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
        result(workimg);
        finished();
    }
}

void PerfectReflectFilter::FindMax()
{
    for (point.x = 0; point.x < resimg.width(); ++point.x)
    {
        for (point.y = 0; point.y < resimg.height(); ++point.y)
        {
            QColor col = resimg.pixel(point.x, point.y);
            if (col.red() > maxR)
                maxR = col.red();
            if (col.green() > maxG)
                maxG = col.green();
            if (col.blue() > maxB)
                maxB = col.blue();
        }
    }
}
