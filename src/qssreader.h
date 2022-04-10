// -----------------------------------------------------------------------------
// Name:           CAJ2PDF Qt
// Description:    CAJ 转 PDF 转换器
// Author:         Aymeric <343894011@qq.com>
// Website:        https://caj2pdf-qt.sainnhe.dev
// License:        GPL3
// -----------------------------------------------------------------------------
#pragma once
#include <QWidget>
class QString;
class QssReader {
public:
    QssReader();

    static bool setCSS(QWidget* object, const QString filename);
};

