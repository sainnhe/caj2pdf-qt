// -----------------------------------------------------------------------------
// Name:           CAJ2PDF Qt
// Description:    CAJ 转 PDF 转换器
// Author:         Sainnhe Park <i@sainnhe.dev>
// Website:        https://caj2pdf-qt.sainnhe.dev
// License:        GPL3
// -----------------------------------------------------------------------------

#include "caj2pdf.h"

/**
 * @brief 开始转换
 *
 */
void CAJ2PDF::convert() {
  this->convertStatus = statusConverting;  // 设置转换状态为正在转换
  for (QString inputFile : this->inputFiles) {  // 遍历所有输入文件
    // 创建一个新线程
    Thread *thread = new Thread(this);
    // 初始化这个线程的参数
    thread->instance = this;
    thread->inputFilePath = inputFile;
    // 开始运行
    thread->start();
  }
  this->convertStatus = statusFinished;  // 设置转换状态为转换结束
  this->page3NextButton->setDisabled(false);  // 启用第三页的“完成”按钮
}

/**
 * @brief 开始转换
 *
 * 该方法将会在调用 start() 后执行
 *
 */
void Thread::run() {
  // caj2pdf 和 mutool 的路径
  QString caj2pdfExecutablePath =
      QDir(QDir(instance->currentDir).filePath(tr("external")))
          .filePath(tr("caj2pdf"));
  QString mutoolExecutablePath =
      QDir(QDir(instance->currentDir).filePath(tr("external")))
          .filePath(tr("mutool"));
  // 从 inputFilePath 这个文件绝对路径获得输入文件的文件名（含扩展名）
  std::string inputFileName = inputFilePath.toStdString().substr(
      inputFilePath.toStdString().find_last_of("/\\") + 1);
  // 输出文件的文件名。将输入文件的扩展名替换成 .pdf
  std::string outputFileName =
      inputFileName.substr(0, inputFileName.find_last_of(".")) + ".pdf";
  // 输出文件的绝对路径
  QString outputFile = QDir(QString::fromStdString(instance->outputDirectory))
                           .filePath(QString::fromStdString(outputFileName));
  // 执行命令，成功返回 0
  QProcess process;
  QStringList args = {QString::fromUtf8("convert"), inputFilePath,
                      QString::fromUtf8("-o"),      outputFile,
                      QString::fromUtf8("-m"),      mutoolExecutablePath};
  // 开始执行命令，并根据结果更新第三页的页面
  if (process.execute(caj2pdfExecutablePath, args) == 0) {
    instance->statusTextBrowser->insertPlainText(
        QString::fromStdString("✅ " + inputFilePath.toStdString() + "\n"));
  } else {
    instance->statusTextBrowser->insertPlainText(
        QString::fromStdString("❌ " + inputFilePath.toStdString() + "\n"));
  }
  // 更新进度条
  instance->progressBar->setValue(instance->progressBar->value() + 1);
}
