#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <utility> 
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Connect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Connect()
{
    //при получении сигнала, обновляется сцена
    connect(this, SIGNAL(update()), this, SLOT(UpdateScene()));

    //соединение пунктов меню
    //работа с файлом
    connect(ui->open, SIGNAL(triggered()), this, SLOT(workWithFile()));             //открыть файл
    connect(ui->save, SIGNAL(triggered()), this, SLOT(workWithFile()));             //сохранить файл
    connect(ui->saveas, SIGNAL(triggered()), this, SLOT(workWithFile()));           //сохранить как
    connect(ui->close, SIGNAL(triggered()), this, SLOT(workWithFile()));            //закрыть файл
    //отменить изменение, повторить
    connect(ui->undo, SIGNAL(triggered()), this, SLOT(PressUndo()));                //отменить последнее действие
    connect(ui->redo, SIGNAL(triggered()), this, SLOT(PressRedo()));                //вернуть изменение
    //вызов фильтра
    connect(ui->inverse, SIGNAL(triggered()), this, SLOT(callFilter()));            //инверсия
    connect(ui->BlWh, SIGNAL(triggered()), this, SLOT(callFilter()));               //черно-белый
    connect(ui->blur, SIGNAL(triggered()), this, SLOT(callFilter()));               //размытие
    connect(ui->sepia, SIGNAL(triggered()), this, SLOT(callFilter()));              //сепия
    connect(ui->sharp, SIGNAL(triggered()), this, SLOT(callFilter()));              //резкость
    connect(ui->brightness, SIGNAL(triggered()), this, SLOT(callFilter()));         //яркость
    connect(ui->sobelX, SIGNAL(triggered()), this, SLOT(callFilter()));             //оператор СобеляХ
    connect(ui->sobelY, SIGNAL(triggered()), this, SLOT(callFilter()));             //оператор СобеляУ
    connect(ui->gaussianBlurring, SIGNAL(triggered()), this, SLOT(callFilter()));   //размытие по Гауссу
    connect(ui->emboss, SIGNAL(triggered()), this, SLOT(callFilter()));             //тиснение
    connect(ui->wave1, SIGNAL(triggered()), this, SLOT(callFilter()));              //Волна1
    connect(ui->wave2, SIGNAL(triggered()), this, SLOT(callFilter()));              //Волна2
    connect(ui->transf, SIGNAL(triggered()), this, SLOT(callFilter()));             //перенос
    connect(ui->turn, SIGNAL(triggered()), this, SLOT(callFilter()));               //поворот
    connect(ui->median, SIGNAL(triggered()), this, SLOT(callFilter()));             //медианный фильтр
    connect(ui->maximum, SIGNAL(triggered()), this, SLOT(callFilter()));            //фильтр максимума
    connect(ui->glowingEdges, SIGNAL(triggered()), this, SLOT(callFilter()));       //светящиеся края
    connect(ui->grayWorld, SIGNAL(triggered()), this, SLOT(callFilter()));          //серый мир
    connect(ui->autolevel, SIGNAL(triggered()), this, SLOT(callFilter()));          //растяжение гистограммы
    connect(ui->dilation, SIGNAL(triggered()), this, SLOT(callFilter()));           //матморфолог расширение
    connect(ui->erosion, SIGNAL(triggered()), this, SLOT(callFilter()));            //матморфолог сужение
    connect(ui->opening, SIGNAL(triggered()), this, SLOT(callFilter()));            //матморфолог открытие
    connect(ui->closing, SIGNAL(triggered()), this, SLOT(callFilter()));            //матморфолог закрытие
    connect(ui->tophat, SIGNAL(triggered()), this, SLOT(callFilter()));            //матморфолог TopHat

}

bool MainWindow::setImage(const QString& _str) //установка изображения
{
    workImg = QPixmap( _str );
    if (!setScene(workImg))
    {
        this->statusBar()->showMessage("Error set Scene");
        return false;
    }
    return true;
}

bool MainWindow::setImage(QPixmap _pix) //установка изображения
{
    workImg = std::move(_pix);
    if (!setScene(workImg))
    {
        this->statusBar()->showMessage("Error set Scene");
        return false;
    }
    return true;
}

bool MainWindow::setScene(const QPixmap& _pix) //установка сцены
{
    //создание сцены
    QGraphicsScene *scn = new QGraphicsScene( ui->view );
    scn->setSceneRect( 0, 0, _pix.width(), _pix.height() );
    ui->view->setScene( scn );
    //установка изображения на сцену
    return scn->addPixmap( _pix ) != nullptr;
}

bool MainWindow::pushStack() //добавить в стек отмены
{
    int sizeS = stackUndo.size();
    stackUndo.push(workImg);
    if (sizeS < stackUndo.size())
    {
        ui->undo->setEnabled(true);
        ui->save->setEnabled(true);
        ui->saveas->setEnabled(true);
        return true;
    }
    return false;
}

void MainWindow::openFile() //открытиь файла
{
    if (nameFile != "")
    {
        closeFile();
    }

    nameFile = QFileDialog::getOpenFileName(nullptr,
                                            "Выбрать файл",
                                            "",
                                            "*.jpg *.png *.bmp");

    if (!setImage(nameFile))
        this->statusBar()->showMessage(tr("File loading is fail"));
    if (nameFile != "")
    {
        changeEnable(true);
    }
}

void MainWindow::closeFile() //закрыть файл
{
    if (nameFile != "")
    {
        QFile file(nameFile);
        file.close();
        nameFile = "";
        changeEnable(false); //отключение элементов меню на false, за мсключением пункта "открыть"
        ui->view->scene()->clear();
    }
    else
    {
        this->statusBar()->showMessage("Файл не открыт");
    }
}

void MainWindow::close()        //закрыть
{
    if (!stackUndo.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("Изображение было изменено");
        msgBox.setInformativeText("Хотите сохранить изменения?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        msgBox.setButtonText(QMessageBox::Discard, tr("Не сохранять"));
        int ret = msgBox.exec();

        switch (ret) {
        case QMessageBox::Save:
            return saveFile(true, false);
        case QMessageBox::Discard:
            return closeFile();
        default:
            break;
        }
    }
    else
    {
        closeFile();
    }
}

void MainWindow::saveFile(bool NeedClose, bool ChangeWay) //сохранить файл
{
    QString errorMessage;

    if (nameFile != "")
    {

        if (ChangeWay) //если необходимо выбрать другое место сохранения
            nameFile = QFileDialog::getSaveFileName(nullptr,
                                                    "Сохранить файл",
                                                    "",
                                                    "*.jpg *.png *.bmp");
        workImg.save(nameFile);
        if (NeedClose) //если необходимо закрыть файл
            closeFile();
        ui->save->setEnabled(false);
        ui->saveas->setEnabled(false);
        ui->undo->setEnabled(false);
        ui->redo->setEnabled(false);
        stackRedo.resize(0);
        stackUndo.resize(0);
    }
    else
    {
        this->statusBar()->showMessage("Файл не открыт");
    }
}

void MainWindow::changeEnable(bool F) //включить/отключить кнопки меню
{
    ui->close->setEnabled(F);
    ui->BlWh->setEnabled(F);
    ui->blur->setEnabled(F);
    ui->sepia->setEnabled(F);
    ui->sharp->setEnabled(F);
    ui->inverse->setEnabled(F);
    ui->brightness->setEnabled(F);
    ui->sobelFilter->setEnabled(F);
    ui->sobelX->setEnabled(F);
    ui->sobelY->setEnabled(F);
    ui->gaussianBlurring->setEnabled(F);
    ui->emboss->setEnabled(F);
    ui->wave->setEnabled(F);
    ui->wave1->setEnabled(F);
    ui->wave2->setEnabled(F);
    ui->transf->setEnabled(F);
    ui->turn->setEnabled(F);
    ui->median->setEnabled(F);
    ui->maximum->setEnabled(F);
    ui->glowingEdges->setEnabled(F);
    ui->grayWorld->setEnabled(F);
    ui->autolevel->setEnabled(F);
    ui->mat_morphology->setEnabled(F);
    ui->dilation->setEnabled(F);
    ui->erosion->setEnabled(F);
    ui->opening->setEnabled(F);
    ui->closing->setEnabled(F);
    ui->tophat->setEnabled(F);

    if (!F)
    {
        ui->undo->setEnabled(F);
        ui->redo->setEnabled(F);
        ui->save->setEnabled(F);
        ui->saveas->setEnabled(F);
    }
}

int **MainWindow::GetStructElement() //получить структурный элемент из иджета
{
    auto* structE = new StructElem();
    structE->setWindowModality(Qt::WindowModal);
    structE->exec();
    int** _kern = structE->GetElem();
    return _kern;
}

//Слоты--------------------------------------------------------------------------------Слоты

void MainWindow::PressUndo()    //нажатие "Отмена"
{
    if (!stackUndo.isEmpty())
    {
        stackRedo.push(workImg);
        if (!setImage(stackUndo.pop()))
            this->statusBar()->showMessage("Ошибка");
        if (stackUndo.isEmpty())
            ui->undo->setEnabled(false);
        ui->redo->setEnabled(true);
    }
}

void MainWindow::PressRedo()    //нажатие "Повторить"
{
    if (!stackRedo.isEmpty())
    {
        stackUndo.push(workImg);
        if (!setImage(stackRedo.pop()))
            this->statusBar()->showMessage("Ошибка");
        if (stackRedo.isEmpty())
            ui->redo->setEnabled(false);
        ui->undo->setEnabled(true);
    }
}

void MainWindow::workWithFile()     //открыть файл
{
    auto* action = qobject_cast<QAction*>(sender());
    this->statusBar()->showMessage(action->text());

    if (action == ui->open)
    {
        openFile();
    }
    else if (action == ui->save)
    {
        saveFile(false, false);
    }
    else if (action == ui->saveas)
    {
        saveFile(false, true);
    }
    else if (action == ui->close)
    {
        close();
    }
}

void MainWindow::callFilter()   //вызов фильтра
{
    QAction* action = qobject_cast<QAction*>(sender());
    this->statusBar()->showMessage(action->text());

    QThread* thread = new QThread;

    ui->ButtonBack->setEnabled(true);
    if (pushStack())
    {
        stackRedo.resize(0);
        ui->redo->setEnabled(false);
        if (action == ui->inverse)
        {
            InverseFilter* fil = new InverseFilter(workImg);
            fil->moveToThread(thread);
            connect(fil, SIGNAL(process(int)), ui->progressJob, SLOT(setValue(int)), Qt::DirectConnection);
            connect(fil, SIGNAL(result(QPixmap)), this, SLOT(GetResult(QPixmap)), Qt::DirectConnection);
            connect(fil, SIGNAL(finished()), fil, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(this, SIGNAL(done()), fil, SLOT(stop()), Qt::DirectConnection);
            connect(thread, SIGNAL(started()), fil, SLOT(Go()));


        } else if (action == ui->BlWh)
        {
            BlackWhiteFilter* fil = new BlackWhiteFilter(workImg);

            fil->moveToThread(thread);
            connect(fil, SIGNAL(process(int)), ui->progressJob, SLOT(setValue(int)), Qt::DirectConnection);
            connect(fil, SIGNAL(result(QPixmap)), this, SLOT(GetResult(QPixmap)), Qt::DirectConnection);
            connect(fil, SIGNAL(finished()), fil, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(this, SIGNAL(done()), fil, SLOT(stop()), Qt::DirectConnection);
            connect(thread, SIGNAL(started()), fil, SLOT(Go()));


        } else if (action == ui->sepia)
        {
            SepiaFilter* fil = new SepiaFilter(workImg);

            fil->moveToThread(thread);
            connect(fil, SIGNAL(process(int)), ui->progressJob, SLOT(setValue(int)), Qt::DirectConnection);
            connect(fil, SIGNAL(result(QPixmap)), this, SLOT(GetResult(QPixmap)), Qt::DirectConnection);
            connect(fil, SIGNAL(finished()), fil, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(this, SIGNAL(done()), fil, SLOT(stop()), Qt::DirectConnection);
            connect(thread, SIGNAL(started()), fil, SLOT(Go()));


        } else if (action == ui->brightness)
        {
            BrightnessFilter* fil = new BrightnessFilter(workImg);

            fil->moveToThread(thread);
            connect(fil, SIGNAL(process(int)), ui->progressJob, SLOT(setValue(int)), Qt::DirectConnection);
            connect(fil, SIGNAL(result(QPixmap)), this, SLOT(GetResult(QPixmap)), Qt::DirectConnection);
            connect(fil, SIGNAL(finished()), fil, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(this, SIGNAL(done()), fil, SLOT(stop()), Qt::DirectConnection);
            connect(thread, SIGNAL(started()), fil, SLOT(Go()));


        } else if (action == ui->blur)
        {
            BlurFilter* fil = new BlurFilter(workImg);

            fil->moveToThread(thread);
            connect(fil, SIGNAL(process(int)), ui->progressJob, SLOT(setValue(int)), Qt::DirectConnection);
            connect(fil, SIGNAL(result(QPixmap)), this, SLOT(GetResult(QPixmap)), Qt::DirectConnection);
            connect(fil, SIGNAL(finished()), fil, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(this, SIGNAL(done()), fil, SLOT(stop()), Qt::DirectConnection);
            connect(thread, SIGNAL(started()), fil, SLOT(Go()));


        } else if (action == ui->gaussianBlurring)
        {
            GaussBlurFilter* fil = new GaussBlurFilter(workImg);

            fil->moveToThread(thread);
            connect(fil, SIGNAL(process(int)), ui->progressJob, SLOT(setValue(int)), Qt::DirectConnection);
            connect(fil, SIGNAL(result(QPixmap)), this, SLOT(GetResult(QPixmap)), Qt::DirectConnection);
            connect(fil, SIGNAL(finished()), fil, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(this, SIGNAL(done()), fil, SLOT(stop()), Qt::DirectConnection);
            connect(thread, SIGNAL(started()), fil, SLOT(Go()));


        } else if (action == ui->sobelX)
        {
            SobelFilter* fil = new SobelFilter(workImg, 'x');

            fil->moveToThread(thread);
            connect(fil, SIGNAL(process(int)), ui->progressJob, SLOT(setValue(int)), Qt::DirectConnection);
            connect(fil, SIGNAL(result(QPixmap)), this, SLOT(GetResult(QPixmap)), Qt::DirectConnection);
            connect(fil, SIGNAL(finished()), fil, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(this, SIGNAL(done()), fil, SLOT(stop()), Qt::DirectConnection);
            connect(thread, SIGNAL(started()), fil, SLOT(Go()));


        } else if (action == ui->sobelY)
        {
            SobelFilter* fil = new SobelFilter(workImg, 'y');

            fil->moveToThread(thread);
            connect(fil, SIGNAL(process(int)), ui->progressJob, SLOT(setValue(int)), Qt::DirectConnection);
            connect(fil, SIGNAL(result(QPixmap)), this, SLOT(GetResult(QPixmap)), Qt::DirectConnection);
            connect(fil, SIGNAL(finished()), fil, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(this, SIGNAL(done()), fil, SLOT(stop()), Qt::DirectConnection);
            connect(thread, SIGNAL(started()), fil, SLOT(Go()));


        } else if (action == ui->sharp)
        {
            SharpFilter* fil = new SharpFilter(workImg);

            fil->moveToThread(thread);
            connect(fil, SIGNAL(process(int)), ui->progressJob, SLOT(setValue(int)), Qt::DirectConnection);
            connect(fil, SIGNAL(result(QPixmap)), this, SLOT(GetResult(QPixmap)), Qt::DirectConnection);
            connect(fil, SIGNAL(finished()), fil, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(this, SIGNAL(done()), fil, SLOT(stop()), Qt::DirectConnection);
            connect(thread, SIGNAL(started()), fil, SLOT(Go()));


        } else if (action == ui->emboss)
        {
            EmbossFilter* fil = new EmbossFilter(workImg);

            fil->moveToThread(thread);
            connect(fil, SIGNAL(process(int)), ui->progressJob, SLOT(setValue(int)), Qt::DirectConnection);
            connect(fil, SIGNAL(result(QPixmap)), this, SLOT(GetResult(QPixmap)), Qt::DirectConnection);
            connect(fil, SIGNAL(finished()), fil, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(this, SIGNAL(done()), fil, SLOT(stop()), Qt::DirectConnection);
            connect(thread, SIGNAL(started()), fil, SLOT(Go()));


        } else if (action == ui->wave1)
        {
            Wave1Filter* fil = new Wave1Filter(workImg);

            fil->moveToThread(thread);
            connect(fil, SIGNAL(process(int)), ui->progressJob, SLOT(setValue(int)), Qt::DirectConnection);
            connect(fil, SIGNAL(result(QPixmap)), this, SLOT(GetResult(QPixmap)), Qt::DirectConnection);
            connect(fil, SIGNAL(finished()), fil, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(this, SIGNAL(done()), fil, SLOT(stop()), Qt::DirectConnection);
            connect(thread, SIGNAL(started()), fil, SLOT(Go()));


        } else if (action == ui->wave2)
        {
            Wave2Filter* fil = new Wave2Filter(workImg);

            fil->moveToThread(thread);
            connect(fil, SIGNAL(process(int)), ui->progressJob, SLOT(setValue(int)), Qt::DirectConnection);
            connect(fil, SIGNAL(result(QPixmap)), this, SLOT(GetResult(QPixmap)), Qt::DirectConnection);
            connect(fil, SIGNAL(finished()), fil, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(this, SIGNAL(done()), fil, SLOT(stop()), Qt::DirectConnection);
            connect(thread, SIGNAL(started()), fil, SLOT(Go()));


        } else if (action == ui->transf)
        {
            TransferFilter* fil = new TransferFilter(workImg);

            fil->moveToThread(thread);
            connect(fil, SIGNAL(process(int)), ui->progressJob, SLOT(setValue(int)), Qt::DirectConnection);
            connect(fil, SIGNAL(result(QPixmap)), this, SLOT(GetResult(QPixmap)), Qt::DirectConnection);
            connect(fil, SIGNAL(finished()), fil, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(this, SIGNAL(done()), fil, SLOT(stop()), Qt::DirectConnection);
            connect(thread, SIGNAL(started()), fil, SLOT(Go()));


        } else if (action == ui->turn)
        {
            TurnFilter* fil = new TurnFilter(workImg);

            fil->moveToThread(thread);
            connect(fil, SIGNAL(process(int)), ui->progressJob, SLOT(setValue(int)), Qt::DirectConnection);
            connect(fil, SIGNAL(result(QPixmap)), this, SLOT(GetResult(QPixmap)), Qt::DirectConnection);
            connect(fil, SIGNAL(finished()), fil, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(this, SIGNAL(done()), fil, SLOT(stop()), Qt::DirectConnection);
            connect(thread, SIGNAL(started()), fil, SLOT(Go()));


        } else if (action == ui->median)
        {
            MedianFilter* fil = new MedianFilter(workImg);

            fil->moveToThread(thread);
            connect(fil, SIGNAL(process(int)), ui->progressJob, SLOT(setValue(int)), Qt::DirectConnection);
            connect(fil, SIGNAL(result(QPixmap)), this, SLOT(GetResult(QPixmap)), Qt::DirectConnection);
            connect(fil, SIGNAL(finished()), fil, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(this, SIGNAL(done()), fil, SLOT(stop()), Qt::DirectConnection);
            connect(thread, SIGNAL(started()), fil, SLOT(Go()));


        } else if (action == ui->maximum)
        {
            MaximumFilter* fil = new MaximumFilter(workImg);

            fil->moveToThread(thread);
            connect(fil, SIGNAL(process(int)), ui->progressJob, SLOT(setValue(int)), Qt::DirectConnection);
            connect(fil, SIGNAL(result(QPixmap)), this, SLOT(GetResult(QPixmap)), Qt::DirectConnection);
            connect(fil, SIGNAL(finished()), fil, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(this, SIGNAL(done()), fil, SLOT(stop()), Qt::DirectConnection);
            connect(thread, SIGNAL(started()), fil, SLOT(Go()));


        } else if (action == ui->glowingEdges)
        {
            GlowingEdgesFilter* fil = new GlowingEdgesFilter(workImg);

            fil->moveToThread(thread);
            connect(fil, SIGNAL(process(int)), ui->progressJob, SLOT(setValue(int)), Qt::DirectConnection);
            connect(fil, SIGNAL(result(QPixmap)), this, SLOT(GetResult(QPixmap)), Qt::DirectConnection);
            connect(fil, SIGNAL(finished()), fil, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(this, SIGNAL(done()), fil, SLOT(stop()), Qt::DirectConnection);
            connect(thread, SIGNAL(started()), fil, SLOT(Go()));


        } else if (action == ui->grayWorld)
        {
            GrayWorldFilter* fil = new GrayWorldFilter(workImg);

            fil->moveToThread(thread);
            connect(fil, SIGNAL(process(int)), ui->progressJob, SLOT(setValue(int)), Qt::DirectConnection);
            connect(fil, SIGNAL(result(QPixmap)), this, SLOT(GetResult(QPixmap)), Qt::DirectConnection);
            connect(fil, SIGNAL(finished()), fil, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(this, SIGNAL(done()), fil, SLOT(stop()), Qt::DirectConnection);
            connect(thread, SIGNAL(started()), fil, SLOT(Go()));


        } else if (action == ui->autolevel)
        {
            AutoLevelFilter* fil = new AutoLevelFilter(workImg);

            fil->moveToThread(thread);
            connect(fil, SIGNAL(process(int)), ui->progressJob, SLOT(setValue(int)), Qt::DirectConnection);
            connect(fil, SIGNAL(result(QPixmap)), this, SLOT(GetResult(QPixmap)), Qt::DirectConnection);
            connect(fil, SIGNAL(finished()), fil, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(this, SIGNAL(done()), fil, SLOT(stop()), Qt::DirectConnection);
            connect(thread, SIGNAL(started()), fil, SLOT(Go()));


        } else if (action == ui->dilation)
        {
            MathMorphology* fil = new MathMorphology(workImg);

            int** kk = GetStructElement();
            fil->SetStructEl(kk);
            fil->moveToThread(thread);
            connect(fil, SIGNAL(process(int)), ui->progressJob, SLOT(setValue(int)), Qt::DirectConnection);
            connect(fil, SIGNAL(result(QPixmap)), this, SLOT(GetResult(QPixmap)), Qt::DirectConnection);
            connect(fil, SIGNAL(finished()), fil, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(this, SIGNAL(done()), fil, SLOT(stop()), Qt::DirectConnection);
            connect(thread, SIGNAL(started()), fil, SLOT(Dilation()));


        } else if (action == ui->erosion)
        {
            MathMorphology* fil = new MathMorphology(workImg);

            int** kk = GetStructElement();
            fil->SetStructEl(kk);
            fil->moveToThread(thread);
            connect(fil, SIGNAL(process(int)), ui->progressJob, SLOT(setValue(int)), Qt::DirectConnection);
            connect(fil, SIGNAL(result(QPixmap)), this, SLOT(GetResult(QPixmap)), Qt::DirectConnection);
            connect(fil, SIGNAL(finished()), fil, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(this, SIGNAL(done()), fil, SLOT(stop()), Qt::DirectConnection);
            connect(thread, SIGNAL(started()), fil, SLOT(Erosion()));


        } else if (action == ui->opening)
        {
            MathMorphology* fil = new MathMorphology(workImg);

            int** kk = GetStructElement();
            fil->SetStructEl(kk);
            fil->moveToThread(thread);
            connect(fil, SIGNAL(process(int)), ui->progressJob, SLOT(setValue(int)), Qt::DirectConnection);
            connect(fil, SIGNAL(result(QPixmap)), this, SLOT(GetResult(QPixmap)), Qt::DirectConnection);
            connect(fil, SIGNAL(finished()), fil, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(this, SIGNAL(done()), fil, SLOT(stop()), Qt::DirectConnection);
            connect(thread, SIGNAL(started()), fil, SLOT(Opening()));


        } else if (action == ui->closing)
        {
            MathMorphology* fil = new MathMorphology(workImg);

            int** kk = GetStructElement();
            fil->SetStructEl(kk);
            fil->moveToThread(thread);
            connect(fil, SIGNAL(process(int)), ui->progressJob, SLOT(setValue(int)), Qt::DirectConnection);
            connect(fil, SIGNAL(result(QPixmap)), this, SLOT(GetResult(QPixmap)), Qt::DirectConnection);
            connect(fil, SIGNAL(finished()), fil, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(this, SIGNAL(done()), fil, SLOT(stop()), Qt::DirectConnection);
            connect(thread, SIGNAL(started()), fil, SLOT(Closing()));


        } else if (action == ui->tophat)
        {
            MathMorphology* fil = new MathMorphology(workImg);

            int** kk = GetStructElement();
            fil->SetStructEl(kk);
            fil->moveToThread(thread);
            connect(fil, SIGNAL(process(int)), ui->progressJob, SLOT(setValue(int)), Qt::DirectConnection);
            connect(fil, SIGNAL(result(QPixmap)), this, SLOT(GetResult(QPixmap)), Qt::DirectConnection);
            connect(fil, SIGNAL(finished()), fil, SLOT(deleteLater()));
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(this, SIGNAL(done()), fil, SLOT(stop()), Qt::DirectConnection);
            connect(thread, SIGNAL(started()), fil, SLOT(TopHat()));

        }
        thread->start();

    }
    else
    {
        this->statusBar()->showMessage("Не удалось добавить изображение в стек");
    }

}

void MainWindow::GetResult(QPixmap pix)
{
    workImg = std::move(pix);
    ui->progressJob->setValue(0);
    emit update();
}

void MainWindow::on_ButtonBack_clicked()
{
    ui->ButtonBack->setEnabled(false);
    emit done();
    ui->progressJob->setValue(0);
}

void MainWindow::UpdateScene()
{
    ui->ButtonBack->setEnabled(false);
    //создание сцены
    QGraphicsScene *scn = new QGraphicsScene( ui->view );
    scn->setSceneRect( 0, 0, workImg.width(), workImg.height() );
    ui->view->setScene( scn );
    //установка изображения на сцену
    if (scn->addPixmap( workImg ))
        this->statusBar()->showMessage("Ok");}
