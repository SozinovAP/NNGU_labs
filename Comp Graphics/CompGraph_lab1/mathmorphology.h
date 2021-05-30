#ifndef MATHMORPHOLOGY_H
#define MATHMORPHOLOGY_H

#include "FilterLibrary.h"
#include <QBitmap>

struct pixelMath
{
    int x;
    int y;
};

class MathMorphology : public QObject
{
    Q_OBJECT
private:
    QPixmap workimg;
    QPixmap resimg;
    QImage tmpImg;
    int SizeX;
    int SizeY;
    int** kernel = nullptr;
    bool F = true;
    bool IsLastFilter = true;
    pixelMath point{};

    QColor CalculNewColor(pixelMath _point);
    int Clamp(int value, int min, int max);
public:
    MathMorphology(QPixmap pix);

    void SetStructEl(int** _kern);


signals:
    void process(int);
    void result(QPixmap);
    void finished();
public slots:
    void stop();
    void Dilation();
    void Erosion();
    void Opening();
    void Closing();
    void TopHat();
    QPixmap Subtraction();

};

#endif // MATHMORPHOLOGY_H
