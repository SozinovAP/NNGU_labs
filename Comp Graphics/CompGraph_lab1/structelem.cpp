#include "structelem.h"
#include "ui_structelem.h"

StructElem::StructElem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StructElem)
{
    ui->setupUi(this);
}

StructElem::~StructElem()
{
    delete ui;
}

int **StructElem::GetElem()
{
    int** elem = new int*[3];
    elem[0] = new int[9];
    for (int i = 1; i != 3; ++i)
    {
        elem[i] = elem[i - 1] + 3;
    }
    elem[0][0] = ui->spinBox00->value();
    elem[0][1] = ui->spinBox01->value();
    elem[0][2] = ui->spinBox02->value();
    elem[1][0] = ui->spinBox10->value();
    elem[1][1] = ui->spinBox11->value();
    elem[1][2] = ui->spinBox12->value();
    elem[2][0] = ui->spinBox20->value();
    elem[2][1] = ui->spinBox21->value();
    elem[2][2] = ui->spinBox22->value();

    return elem;
}
