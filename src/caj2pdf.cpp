#include "caj2pdf.h"
#include "./ui_caj2pdf.h"

CAJ2PDF::CAJ2PDF(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CAJ2PDF)
{
    ui->setupUi(this);
}

CAJ2PDF::~CAJ2PDF()
{
    delete ui;
}

