#include "filter.h"
#include <QDebug>
#include <utility> 
Filter::Filter(QPixmap pix)
{
    this->workimg = std::move(pix);
}

Filter::~Filter() = default;

void Filter::ProcImg()
{
    QImage resPix = workimg.toImage();
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

int Filter::Clamp(int value, int min, int max)
{
    if (value < min)
    {
        return min;
    }
    if (value > max)
    {
        return max;
    }
    
    
        return value;
    
}


void Filter::ResultImg(const QPixmap& pix)
{
    resimg = pix.toImage();
}

void Filter::stop()
{
    F = false;
}

void Filter::Go()
{
    ProcImg();
}




MatrixFilter::MatrixFilter(const QPixmap& pix) : Filter(pix)
{
    SizeX = 1;
    SizeY = 1;
    kernel = new float* [SizeX];
    kernel[0] = new float[SizeX * SizeY];
    for (int i = 1; i != SizeX; ++i)
    {
        kernel[i] = kernel[i - 1] + SizeY;
    }
}

MatrixFilter::~MatrixFilter()
{
    delete[] kernel[0];
    delete[] kernel;
}

QColor MatrixFilter::CalculNewColor(pixel _point)
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
            int idX = Clamp(_point.x + k, 0, resimg.width() - 1);
            int idY = Clamp(_point.y + l, 0, resimg.height() - 1);
            QColor newCol = resimg.pixel(idX, idY);
            resR += newCol.red() * kernel[k + RadiusX][l + RadiusY];
            resG += newCol.green() * kernel[k + RadiusX][l + RadiusY];
            resB += newCol.blue() * kernel[k + RadiusX][l + RadiusY];
        }
    }
    return QColor::fromRgb(Clamp(static_cast<int>(resR), 0, 255),
                        Clamp(static_cast<int>(resG), 0, 255),
                        Clamp(static_cast<int>(resB), 0, 255));
}

MatrixFilter::MatrixFilter(float **_kern, const QPixmap& pix) : Filter(pix)
{
    kernel = _kern;
}
