#ifndef BACKWORKER_H
#define BACKWORKER_H

#include <QObject>
#include "mainwindow.h"
#include "FilterLibrary.h"
#include <windows.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class BackWorker : public QObject
{
    Q_OBJECT
    Ui::MainWindow *ui{};
    QPixmap img;
    bool tStop = false;
public:
    BackWorker(QPixmap _img);
    ~BackWorker();
    QPixmap GetImage();

public slots:
    void doWork(double c);
    void stop();

signals:
    void finished(QPixmap);
    void send(double c);

};

//--------------------------

template <class TypeFilter>
class Work : public BackWorker
{
    TypeFilter filt;
public:
    Work(TypeFilter _filt);
    ~Work();

    void BackWork(QPixmap img);
};
#endif // BACKWORKER_H
