#include "autolevel.h"

void AutoLevelFilter::MaxMin()
{
    for (point.x = 0; point.x < resimg.width(); ++point.x)
    {
        for (point.y = 0; point.y < resimg.height(); ++point.y)
        {
           QColor col = resimg.pixel(point.x, point.y);

           if (col.red() < minR)
               minR = col.red();
           if (col.green() < minG)
               minG = col.green();
           if (col.blue() < minB)
               minB = col.blue();

           if (col.red() > maxR)
               maxR = col.red();
           if (col.green() > maxG)
               maxG = col.green();
           if (col.blue() > maxB)
               maxB = col.blue();
        }
    }
}

QColor AutoLevelFilter::CalculNewColor(pixel _point)
{
    QColor _col = resimg.pixel(_point.x, _point.y);
    return QColor::fromRgb(Clamp((_col.red() - minR) * 255 / (maxR - minR), 0, 255),
                        Clamp((_col.green() - minG) * 255 / (maxG - minG), 0, 255),
                        Clamp((_col.blue() - minB) * 255 / (maxB - minB), 0, 255));
}

AutoLevelFilter::AutoLevelFilter(const QPixmap& pix) : Filter(pix)
{
    maxR = 0;
    maxG = 0;
    maxB = 0;
    minR = 255;
    minG = 255;
    minB = 255;
}

void AutoLevelFilter::ProcImg()
{
    QImage resPix = workimg.toImage();
    resimg = resPix;

    MaxMin();

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
