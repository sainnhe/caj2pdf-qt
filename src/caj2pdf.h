#ifndef CAJ2PDF_H
#define CAJ2PDF_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class CAJ2PDF; }
QT_END_NAMESPACE

class CAJ2PDF : public QDialog
{
    Q_OBJECT

public:
    CAJ2PDF(QWidget *parent = nullptr);
    ~CAJ2PDF();

private:
    Ui::CAJ2PDF *ui;
};
#endif // CAJ2PDF_H
