// -----------------------------------------------------------------------------
// Name:           CAJ2PDF Qt
// Description:    CAJ 转 PDF 转换器
// Author:         Sainnhe Park <i@sainnhe.dev>
// Website:        https://caj2pdf-qt.sainnhe.dev
// License:        GPL3
// -----------------------------------------------------------------------------

#include "caj2pdf.h"

/**
 * @brief 第三页的上一步按钮
 *
 * 更新 stack 和 navigationList, 切换到上一页；
 *
 */
void CAJ2PDF::handlePage3PrevButton() {
  stack->setCurrentIndex(1);
  navigationList->setCurrentRow(1);
}

/**
 * @brief 第三页的完成按钮
 *
 * 这个按钮只有当转换完成后才会被启用；
 *
 * 点击后直接退出应用。
 *
 */
void CAJ2PDF::handlePage3NextButton() { QApplication::quit(); }
