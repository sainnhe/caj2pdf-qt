// -----------------------------------------------------------------------------
// Name:           CAJ2PDF Qt
// Description:    CAJ 转 PDF 转换器
// Author:         Aymeric <343894011@qq.com>
// Website:        https://caj2pdf-qt.sainnhe.dev
// License:        GPL3
// -----------------------------------------------------------------------------
#include "qssreader.h"
#include <QFile>

QssReader::QssReader()
{

}

bool QssReader::setCSS(QWidget* object, const QString filename)
{
    QString str;
    QFile qss(filename);
    if (qss.open(QFile::ReadOnly | QFile::Text)) {
        str = qss.readAll();
        object->setStyleSheet(str);
        qss.close();
        return true;
    }
    return false;
}
