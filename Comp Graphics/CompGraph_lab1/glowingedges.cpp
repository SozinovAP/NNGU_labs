#include "glowingedges.h"

GlowingEdgesFilter::GlowingEdgesFilter(const QPixmap& pix) : MatrixFilter(pix)
{
}

void GlowingEdgesFilter::ProcImg()
{
    //обработка медианным фильтром
    MedianFilter _med(workimg);
    connect(&_med, SIGNAL(result(QPixmap)), this, SLOT(ResultImg(QPixmap)));
   _med.ProcImg();

    //обработка оператором Собеля
    SobelFilter _sob(QPixmap::fromImage(resimg));
    connect(&_sob, SIGNAL(result(QPixmap)), this, SLOT(ResultImg(QPixmap)));
    _sob.ProcImg();

    //обработка фильтром Максимума
    MaximumFilter _max(QPixmap::fromImage(resimg));
    connect(&_max, SIGNAL(result(QPixmap)), this, SLOT(ResultImg(QPixmap)));
    _max.ProcImg();

    if (F)
    {
        workimg = QPixmap::fromImage(resimg);
    }
    result(workimg);
    finished();
}

void GlowingEdgesFilter::ResultImg(const QPixmap& pix)
{
    resimg = pix.toImage();
}
