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
 * @param instance 待转换的 CAJ2PDF 对象
 */
void CAJ2PDF::convert(CAJ2PDF *instance) {
  instance->convertStatus = statusConverting;  // 设置转换状态为正在转换
  for (QString inputFile : instance->inputFiles) {  // 遍历所有输入文件
    Convert *convertor = new Convert();  // 实例化一个 Convert 对象
    // 当 Convert 对象发送 requestUpdateUI 信号时, CAJ2PDF *instance
    // 对象根据发送过来的相应的信息更新界面
    connect(convertor, SIGNAL(requestUpdateUI(int, std::string)), instance,
            SLOT(updatePage3UI(int, std::string)));
    convertor->handleConvert(instance, inputFile);  // 开始转换
  }
  instance->convertStatus = statusFinished;  // 设置转换状态为转换结束
  instance->page3NextButton->setDisabled(false);  // 启用第三页的“完成”按钮
}

/**
 * @brief 更新第三页的界面
 *
 * @param returnCode 转换程序的返回值，若为 0 则代表转换成功，否则转换失败
 * @param inputFile 输入文件名
 */
void CAJ2PDF::updatePage3UI(int returnCode, std::string inputFile) {
  progressBar->setValue(progressBar->value() + 1);  // 更新进度条
  if (returnCode == 0) {
    statusTextBrowser->insertPlainText(
        QString::fromStdString("✅ " + inputFile + "\n"));
  } else {
    statusTextBrowser->insertPlainText(
        QString::fromStdString("❌ " + inputFile + "\n"));
  }
}

/**
 * @brief 开始转换
 *
 * @param instance 待转换的实例
 * @param inputFilePath 输入文件路径
 */
void Convert::handleConvert(CAJ2PDF *instance, QString inputFilePath) {
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
  emit requestUpdateUI(process.execute(caj2pdfExecutablePath, args),
                       inputFilePath.toStdString());
}
