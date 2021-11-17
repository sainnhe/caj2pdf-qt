#include "caj2pdf.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CAJ2PDF w;
    w.show();
    return a.exec();
}
