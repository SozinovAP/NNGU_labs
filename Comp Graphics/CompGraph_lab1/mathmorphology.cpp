#include "mathmorphology.h"
 #include <utility> 

QColor MathMorphology::CalculNewColor(pixelMath _point)
{
    QColor minuendC = workimg.toImage().pixel(_point.x, _point.y);
    QColor subtrahendC = resimg.toImage().pixel(_point.x, _point.y);
    return QColor::fromRgb(Clamp(minuendC.red() - subtrahendC.red(), 0, 255),
                           Clamp(minuendC.green() - subtrahendC.green(), 0, 255),
                           Clamp(minuendC.blue() - subtrahendC.blue(), 0, 255));
}

int MathMorphology::Clamp(int value, int min, int max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

MathMorphology::MathMorphology(QPixmap  pix)
{
    workimg = std::move(pix);
    resimg = workimg;
    SizeX = 3;
    SizeY = 3;
}

void MathMorphology::SetStructEl(int** _kern)
{
    kernel = new int* [SizeX];
    kernel[0] = new int[SizeX * SizeY];

    for (int i = 1; i != SizeX; ++i)
    {
        kernel[i] = kernel[i - 1] + SizeY;
    }
    for (int i = 0; i < SizeX; ++i)
    {
        for (int j = 0; j < SizeY; ++j)
        {
            kernel[i][j] = _kern[i][j];
        }
    }
}

void MathMorphology::Dilation()
{
    QImage sourceImg = workimg.toImage();

    tmpImg = sourceImg;
    QPainter p(&tmpImg);
    for (point.y = SizeY / 2; point.y < workimg.height() - SizeY / 2; ++point.y)
    {
        for (point.x = SizeX / 2; point.x < workimg.width() - SizeX / 2; ++point.x)
        {
            pixelMath m;
            int maxR = 0;
            int maxG = 0;
            int maxB = 0;
            for (m.y = -SizeY / 2; m.y <= SizeY / 2; ++m.y)
            {
                for (m.x = -SizeX / 2; m.x <= SizeX / 2; ++m.x)
                {
                    if (kernel[m.x + SizeX / 2][m.y + SizeY / 2])
                    {
                        if  (sourceImg.pixelColor(point.x + m.x, point.y + m.y).red() > maxR)
                             maxR = sourceImg.pixelColor(point.x + m.x, point.y + m.y).red();
                        if  (sourceImg.pixelColor(point.x + m.x, point.y + m.y).green() > maxG)
                             maxG = sourceImg.pixelColor(point.x + m.x, point.y + m.y).green();
                        if  (sourceImg.pixelColor(point.x + m.x, point.y + m.y).blue() > maxB)
                             maxB = sourceImg.pixelColor(point.x + m.x, point.y + m.y).blue();
                    }

                }
                QColor color = QColor::fromRgb(maxR, maxG, maxB);
                p.setPen(color);
                p.drawPoint(point.x, point.y);
            }
            emit process(100 * (point.y - SizeY / 2) / (workimg.height() - 1 - SizeY / 2));
        }

    }
    if (F)
    {
        resimg = QPixmap::fromImage(tmpImg);
        if (IsLastFilter)
           {
            result(resimg);
            finished();
           }
    }
 }

void MathMorphology::Erosion()
{
    QImage sourceImg = workimg.toImage();

    tmpImg = sourceImg;
    QPainter p(&tmpImg);
    for (point.y = SizeY / 2; point.y < workimg.height() - SizeY / 2; ++point.y)
    {
        for (point.x = SizeX / 2; point.x < workimg.width() - SizeX / 2; ++point.x)
        {
            pixelMath m;
            int minR = 255;
            int minG = 255;
            int minB = 255;
            for (m.y = -SizeY / 2; m.y <= SizeY / 2; ++m.y)
            {
                for (m.x = -SizeX / 2; m.x <= SizeX / 2; ++m.x)
                {
                    if (kernel[m.x + SizeX / 2][m.y + SizeY / 2])
                    {
                        if  (sourceImg.pixelColor(point.x + m.x, point.y + m.y).red() < minR)
                             minR = sourceImg.pixelColor(point.x + m.x, point.y + m.y).red();
                        if  (sourceImg.pixelColor(point.x + m.x, point.y + m.y).green() < minG)
                             minG = sourceImg.pixelColor(point.x + m.x, point.y + m.y).green();
                        if  (sourceImg.pixelColor(point.x + m.x, point.y + m.y).blue() < minB)
                             minB = sourceImg.pixelColor(point.x + m.x, point.y + m.y).blue();
                    }

                }
                QColor color = QColor::fromRgb(minR, minG, minB);
                p.setPen(color);
                p.drawPoint(point.x, point.y);
            }
            emit process(100 * (point.y - SizeY / 2) / (workimg.height() - 1 - SizeY / 2));
        }

    }
    if (F)
    {
        resimg = QPixmap::fromImage(tmpImg);
        if (IsLastFilter)
           {
            result(resimg);
            finished();
           }
    }
}

void MathMorphology::Opening()
{
    Erosion();
    Dilation();

}

void MathMorphology::Closing()
{
    Dilation();
    Erosion();

}

void MathMorphology::TopHat()
{
    tmpImg = workimg.toImage();
    //вычитаемое псле операции Closing хранится в resImg;
    Closing();

    resimg = Subtraction();

    if (F)
    {
        resimg = QPixmap::fromImage(tmpImg);
        result(resimg);
        finished();
    }
}

QPixmap MathMorphology::Subtraction()
{
    QImage sourceImg = workimg.toImage();

    tmpImg = sourceImg;
    QPainter p(&tmpImg);
    for (point.x = 0; point.x != workimg.width(); ++point.x)
    {
        for (point.y = 0; point.y != workimg.height(); ++point.y)
        {
            QColor color = CalculNewColor(point);
            p.setPen(color);
            p.drawPoint(point.x, point.y);
        }
        emit process(100 * point.x / (workimg.width() - 1));
    }
   return QPixmap::fromImage(tmpImg);
}

void MathMorphology::stop()
{
    F = false;
}


