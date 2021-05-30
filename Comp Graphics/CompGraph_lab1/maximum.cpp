#include "maximum.h"

QColor MaximumFilter::CalculNewColor(pixel _point)
{
    int RadiusX = SizeX / 2;
    int RadiusY = SizeY / 2;

    QVector<double> arrF(SizeX * SizeY);
    QVector<QColor> arrC(SizeX * SizeY);

    for (int i = -RadiusX; i <= RadiusX; ++i)
        for (int j = -RadiusY; j <= RadiusY; ++j)
        {
            int idX = Clamp(_point.x + i, 0, resimg.width() - 1);
            int idY = Clamp(_point.y + j, 0, resimg.height() - 1);
            QColor newCol = resimg.pixel(idX, idY);
            arrC[3 * (j + RadiusY) + i + RadiusX] = resimg.pixel(idX, idY);
            double intens = newCol.red() * 0.299 + newCol.green() * 0.587 + newCol.blue() * 0.114;
            arrF[3 * (j + RadiusY) + i + RadiusX] = intens;
        }
    std::sort(arrF.begin(), arrF.end());
    foreach(QColor col, arrC)
    {
        double intens = col.red() * 0.299 + col.green() * 0.587 + col.blue() * 0.114;
        if (intens == arrF[arrF.size() - 1])
        {
            return col;
        }
    }
    return arrC[0];
}

MaximumFilter::MaximumFilter(const QPixmap& pix) : MatrixFilter(pix)
{
    SizeX = 3;
    SizeY = 3;
    kernel = new float* [SizeX];
    kernel[0] = new float[SizeX * SizeY];
    for (int i = 1; i != SizeX; ++i)
    {
        kernel[i] = kernel[i - 1] + SizeY;
    }
}
