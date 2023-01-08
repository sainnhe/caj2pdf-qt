// -----------------------------------------------------------------------------
// Name:           CAJ2PDF Qt
// Description:    CAJ 转 PDF 转换器
// Author:         Sainnhe Park <i@sainnhe.dev>
// Website:        https://caj2pdf-qt.sainnhe.dev
// License:        GPL3
// -----------------------------------------------------------------------------

#include "caj2pdf.h"

#include "./ui_caj2pdf.h"

CAJ2PDF::CAJ2PDF(QWidget *parent, std::string argv0)
    : QDialog(parent), ui(new Ui::CAJ2PDF) {
  version = "0.1.4";
  ui->setupUi(this);
  setAcceptDrops(true);  // 设置支持鼠标推拽
  setWindowFlags(windowFlags() |
                 Qt::WindowContextHelpButtonHint);  // 启用窗口右上角的 ？按钮
  qApp->installEventFilter(this);                   // 安装事件
  convertStatus = statusNotStarted;  // 设置转换状态
  inputFiles = QList<QString>();     // 初始化一个空的 QList<QString>
  uiPage1();                         // 设置第一页的 UI
  uiPage2();                         // 设置第二页的 UI
  uiPage3();                         // 设置第三页的 UI
  uiMain();                          // 设置总体 UI
}

CAJ2PDF::~CAJ2PDF() { delete ui; }

