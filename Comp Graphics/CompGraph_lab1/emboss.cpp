#include "emboss.h"
#include <QDebug>

QColor EmbossFilter::CalculNewColor(pixel  /*_point*/)
{
    int RadiusX = SizeX / 2;
    int RadiusY = SizeY / 2;

    float resR = 0;
    float resG = 0;
    float resB = 0;

    for (int l = -RadiusY; l <= RadiusY; ++l)
    {
        for (int k = -RadiusX; k <= RadiusX; ++k)
        {
            int idX = Clamp(point.x + k, 0, resimg.width() - 1);
            int idY = Clamp(point.y + l, 0, resimg.height() - 1);
            QColor newCol = resimg.pixel(idX, idY);
            resR += newCol.red() * kernel[k + RadiusX][l + RadiusY];
            resG += newCol.green() * kernel[k + RadiusX][l + RadiusY];
            resB += newCol.blue() * kernel[k + RadiusX][l + RadiusY];
        }
    }
    return QColor::fromRgb(Clamp((static_cast<int>(resR) + 255) / 2, 0, 255),
                        Clamp((static_cast<int>(resG) + 255) / 2, 0, 255),
                        Clamp((static_cast<int>(resB) + 255) / 2, 0, 255));
}

EmbossFilter::EmbossFilter(const QPixmap& pix) : MatrixFilter(pix)
{

    SizeX = 3;
    SizeY = 3;
    kernel = new float* [SizeX];
    kernel[0] = new float[SizeX * SizeY];
    for (int i = 1; i != SizeX; ++i)
    {
        kernel[i] = kernel[i - 1] + SizeY;
    }

    kernel[0][0] = 0;
    kernel[0][1] = 1;
    kernel[0][2] = 0;
    kernel[1][0] = 1;
    kernel[1][1] = 0;
    kernel[1][2] = -1;
    kernel[2][0] = 0;
    kernel[2][1] = -1;
    kernel[2][2] = 0;
}

void EmbossFilter::ProcImg()
{
    //перевод в полутоновое
    BlackWhiteFilter _tmpBlWh(workimg);
    connect(&_tmpBlWh, SIGNAL(result(QPixmap)), this, SLOT(ResultImg(QPixmap)));
    _tmpBlWh.ProcImg();

    //применение маски
    QImage resPix = resimg;
    resimg = resPix;
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

