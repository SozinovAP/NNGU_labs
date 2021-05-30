#ifndef STRUCTELEM_H
#define STRUCTELEM_H

#include <QDialog>

namespace Ui {
class StructElem;
}

class StructElem : public QDialog
{
    Q_OBJECT

public:
    explicit StructElem(QWidget *parent = nullptr);
    ~StructElem();
    int** GetElem();
private:
    Ui::StructElem *ui;
};

#endif // STRUCTELEM_H
