#ifndef SOBELFILTER_H
#define SOBELFILTER_H

#include "FilterLibrary.h"

class SobelFilter : public MatrixFilter
{
public:
    SobelFilter(const QPixmap& pix, char mode = 'x');
};

#endif // SOBELFILTER_H
