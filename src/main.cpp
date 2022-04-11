// -----------------------------------------------------------------------------
// Name:           CAJ2PDF Qt
// Description:    CAJ 转 PDF 转换器
// Author:         Sainnhe Park <sainnhe@gmail.com>
// Author:         Aymeric <343894011@qq.com>
// Website:        https://caj2pdf-qt.sainnhe.dev
// License:        GPL3
// -----------------------------------------------------------------------------

//#include "caj2pdf.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char* argv[])
{

#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Floor);
#endif
    QApplication a(argc, argv);
    //CAJ2PDF w(nullptr, argv[0]);
    MainWindow w;
    w.show();
    return a.exec();
}
