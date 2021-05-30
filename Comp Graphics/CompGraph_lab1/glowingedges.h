#ifndef GLOWINGEDGESFILTER_H
#define GLOWINGEDGESFILTER_H

#include "FilterLibrary.h"

class GlowingEdgesFilter : public MatrixFilter
{
public:
    GlowingEdgesFilter(const QPixmap& pix);
    void ProcImg();
public slots:
    void ResultImg(const QPixmap&);
};

#endif // GLOWINGEDGESFILTER_H
