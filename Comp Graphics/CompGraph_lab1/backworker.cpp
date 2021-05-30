#include "backworker.h"
 #include <utility> 
BackWorker::BackWorker(QPixmap _img)
{
    img = std::move(_img);
}

BackWorker::~BackWorker() = default;

QPixmap BackWorker::GetImage()
{
    return img;
}

void BackWorker::doWork(double c)
{
   /* //img = filter.ProcImg(img);
    int i = 0;
    while (!tStop)
    {
        emit send(++i);
        Sleep(100);
    }

    emit finished(img);*/
    emit send(c);
}

void BackWorker::stop()
{
    tStop = true;
}


template<class TypeFilter>
Work<TypeFilter>::Work(TypeFilter _filt)
{
    filt = _filt;
}

template<class TypeFilter>
Work<TypeFilter>::~Work() = default;

template<class TypeFilter>
void Work<TypeFilter>::BackWork(QPixmap img)
{
    filt.ProcImg(img);
}
