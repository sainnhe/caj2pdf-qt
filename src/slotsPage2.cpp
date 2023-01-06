// -----------------------------------------------------------------------------
// Name:           CAJ2PDF Qt
// Description:    CAJ 转 PDF 转换器
// Author:         Sainnhe Park <i@sainnhe.dev>
// Website:        https://caj2pdf-qt.sainnhe.dev
// License:        GPL3
// -----------------------------------------------------------------------------

#include "caj2pdf.h"

/**
 * @brief 第二页的选择输出目录按钮
 *
 * 打开一个目录选择窗口来选择目录，将结果放入 outputDirectory
 *
 */
void CAJ2PDF::handlePage2SelectOutputButton() {
  outputDirectory =
      QFileDialog::getExistingDirectory(
          this, tr("选择目录"), selectOutputLineEdit->text(),
          QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks)
          .toStdString();
  selectOutputLineEdit->setText(QString::fromStdString(outputDirectory));
}

/**
 * @brief 第二页的上一步按钮
 *
 * 更新 stack 和 navigationList, 切换到上一页；
 *
 */
void CAJ2PDF::handlePage2PrevButton() {
  stack->setCurrentIndex(0);
  navigationList->setCurrentRow(0);
}

/**
 * @brief 第二页的下一步按钮
 *
 * 如果转换正在进行中或者已结束，则只更新 stack 和 navigationList 来切换页面；
 *
 * 否则先检测输出目录是否存在，若不存在则弹出一个警告框并返回；
 *
 * 若存在则更新 outputDirectory 和 progressBar ，然后开始异步转换。
 *
 */
void CAJ2PDF::handlePage2NextButton() {
  if (convertStatus == statusNotStarted) {
    if (!QDir(selectOutputLineEdit->text()).exists()) {
      QMessageBox::warning(this, tr("警告"), tr("请选择一个存在的目录"));
      return;
    }
    outputDirectory = selectOutputLineEdit->text().toStdString();
    progressBar->setRange(0, inputFiles.count());
    progressBar->setValue(0);
    QFuture<void> future = QtConcurrent::run(convert, this);
  }
  stack->setCurrentIndex(2);
  navigationList->setCurrentRow(2);
  navigationList->item(2)->setFlags(
      navigationList->item(2)->flags().setFlag(Qt::ItemIsEnabled, true));
}
