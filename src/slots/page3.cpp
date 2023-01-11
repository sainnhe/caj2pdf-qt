// -----------------------------------------------------------------------------
// Name:           CAJ2PDF Qt
// Description:    CAJ 转 PDF 转换器
// Author:         Sainnhe Park <i@sainnhe.dev>
// Website:        https://caj2pdf-qt.sainnhe.dev
// License:        GPL3
// -----------------------------------------------------------------------------

#include "caj2pdf.hpp"

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

/**
 * @brief 更新第三页的转换状态框和进度条
 *
 * @param status 转换是否成功
 * @param inputFilePath 转换文件的路径
 */
void CAJ2PDF::updatePage3Progress(bool status, QString inputFilePath) {
  page3Mutex->lock();
  progressBar->setValue(progressBar->value() + 1);
  if (status) {
    statusTextBrowser->insertPlainText(
        QString::fromStdString("✅ " + inputFilePath.toStdString() + "\n"));
  } else {
    statusTextBrowser->insertPlainText(
        QString::fromStdString("❌ " + inputFilePath.toStdString() + "\n"));
  }
  page3Mutex->unlock();
}

/**
 * @brief 更新第三页的完成按钮，并更新结束状态
 *
 */
void CAJ2PDF::updatePage3FinishedStatus() {
  conversionStatus = Finished;           // 设置转换状态为转换结束
  page3NextButton->setEnabled(true);     // 启用第三页的“完成”按钮
  page3CancelButton->setDisabled(true);  // 禁用第三页的“取消”按钮
  page3PrevButton->setDisabled(true);  // 禁用第三页的“上一步”按钮
  // 禁用侧边栏
  navigationList->item(0)->setFlags(
      navigationList->item(0)->flags().setFlag(Qt::ItemIsEnabled, false));
  navigationList->item(1)->setFlags(
      navigationList->item(1)->flags().setFlag(Qt::ItemIsEnabled, false));
}
