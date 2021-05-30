#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QMenuBar>
#include <QStatusBar>
#include <QAction>
#include <QFileDialog>
#include <QSaveFile>
#include <QImage>
#include <QStack>
#include <QThread>
#include "FilterLibrary.h"
#include "backworker.h"
#include "structelem.h"

#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QPixmap workImg;

private:
    Ui::MainWindow *ui;

    QStack<QPixmap> stackUndo;
    QStack<QPixmap> stackRedo;
    QString nameFile = "";

    void Connect();

    bool setImage(const QString& _str);    //установка изображения
    bool setImage(QPixmap _pix);    //установка изображения
    bool setScene(const QPixmap& _pix);    //установка сцены

    bool pushStack();               //добавить в стек отмены
    void openFile();                //открытиь файла
    void closeFile();               //закрыть файл
    void close();                   //закрыть
    void saveFile(bool NeedClose, bool ChangeWay);  //сохранить файл
    void changeEnable(bool F);      //включить/отключить кнопки меню

    int** GetStructElement();

private slots:
    void on_ButtonBack_clicked();

public slots:
    void UpdateScene();             //обновить сцену
    void PressUndo();               //нажатие "Отмена"
    void PressRedo();               //нажатие "Повторить"
    void workWithFile();            //открыть
    void callFilter();              //вызов фильтра
    void GetResult(QPixmap);
signals:
    void update();
    void done();

};
#endif // MAINWINDOW_H
