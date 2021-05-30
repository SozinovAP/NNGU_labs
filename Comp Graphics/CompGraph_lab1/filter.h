#ifndef FILTER_H
#define FILTER_H

#include <QPixmap>
#include <QImage>
#include <QPainter>

struct pixel
{
    int x;
    int y;
};

class Filter : public QObject
{
    Q_OBJECT
protected:
    pixel point{};
    QPixmap workimg;
    QImage resimg;
    bool F = true;
    virtual QColor CalculNewColor(pixel _point) = 0;
public:
    Filter(QPixmap pix);
    virtual ~Filter();
    virtual void ProcImg();

    int Clamp(int value, int min, int max);
signals:
    void process(int);
    void result(QPixmap);
    void finished();
public slots:
    void ResultImg(const QPixmap&);
    void stop();
    void Go();
};


class MatrixFilter : public Filter
{
protected:
    QColor CalculNewColor(pixel _point);

    int SizeX{};
    int SizeY{};
    float** kernel = nullptr;

public:
    MatrixFilter(const QPixmap& pix);
    ~MatrixFilter();
    MatrixFilter(float** _kern, const QPixmap& pix);

};

#endif // FILTER_H
