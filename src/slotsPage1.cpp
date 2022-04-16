// -----------------------------------------------------------------------------
// Name:           CAJ2PDF Qt
// Description:    CAJ 转 PDF 转换器
// Author:         Sainnhe Park <sainnhe@gmail.com>
// Website:        https://caj2pdf-qt.sainnhe.dev
// License:        GPL3
// -----------------------------------------------------------------------------

#include <QFileDialog>
#include <QVector>
#include <string>

#include "caj2pdf.h"

/**
 * @brief 第一页的选择输入文件按钮
 *
 * 打开一个文件选择窗口，选择一个或多个 CAJ 文件，将结果放入 inputFiles ；
 *
 * 将这些文件的绝对路径写入 inputTextBrowser 和 outputTextBrowser 。
 *
 */
void CAJ2PDF::handlePage1SelectInputButton() {
  // 添加新选择的文件
  inputFiles += QFileDialog::getOpenFileNames(
      this, tr("打开 CAJ 文件"), QDir::homePath(), tr("CAJ 文件 (*.caj)"));
  // 删除重复文件
  QVector<QString> inputFilesVec = inputFiles.toVector();
  std::sort(inputFilesVec.begin(), inputFilesVec.end());
  inputFilesVec.erase(std::unique(inputFilesVec.begin(), inputFilesVec.end()),
                      inputFilesVec.end());
  inputFiles = inputFilesVec.toList();
  // 更新文本框
  QString inputFilesText = tr("");
  for (QString str : inputFiles) {
    inputFilesText = inputFilesText + str + "\n";
  }
  inputTextBrowser->setText(inputFilesText);
  outputTextBrowser->setText(inputFilesText);
}

/**
 * @brief 第一页的下一步按钮
 *
 * 如果未选择任何文件，则弹出一个警告框并返回；
 *
 * 否则更新 stack 和 navigationList, 切换到下一页；
 *
 * 将第一个输入文件所在目录设置为默认输出目录。
 *
 */
void CAJ2PDF::handlePage1NextButton() {
  if (inputFiles.empty()) {
    QMessageBox::warning(this, tr("警告"), tr("未选择 CAJ 文件"));
    return;
  }
  stack->setCurrentIndex(1);
  navigationList->setCurrentRow(1);
  navigationList->item(1)->setFlags(
      navigationList->item(1)->flags().setFlag(Qt::ItemIsEnabled, true));
  std::string defaultDir =
      QFileInfo(inputFiles[0]).absoluteDir().absolutePath().toStdString();
  selectOutputLineEdit->setText(QString::fromStdString(defaultDir));
}
