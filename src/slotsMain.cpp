// -----------------------------------------------------------------------------
// Name:           CAJ2PDF Qt
// Description:    CAJ 转 PDF 转换器
// Author:         Sainnhe Park <i@sainnhe.dev>
// Website:        https://caj2pdf-qt.sainnhe.dev
// License:        GPL3
// -----------------------------------------------------------------------------

#include "caj2pdf.h"

/**
 * @brief 处理取消按钮
 *
 * 若正在转换中，则弹出消息框询问是否确定结束程序；
 *
 * 否则直接结束程序。
 *
 */
void CAJ2PDF::handleCancelButton() {
  if (convertStatus == statusNotStarted || convertStatus == statusFinished) {
    QApplication::quit();
  } else {
    switch (QMessageBox::question(
        this, tr("警告"), tr("转换尚未完成，是否要结束程序？"),
        QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok)) {
      case QMessageBox::Ok:
        QApplication::quit();
        break;
      case QMessageBox::Cancel:
        break;
      default:
        break;
    }
  }
}
