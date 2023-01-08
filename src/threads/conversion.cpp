// -----------------------------------------------------------------------------
// Name:           CAJ2PDF Qt
// Description:    CAJ 转 PDF 转换器
// Author:         Sainnhe Park <i@sainnhe.dev>
// Website:        https://caj2pdf-qt.sainnhe.dev
// License:        GPL3
// -----------------------------------------------------------------------------

#include "caj2pdf.hpp"

/**
 * @brief 转换线程的构造函数
 *
 * @param parent 线程的父对象
 * @param inputFilePath 输入文件路径
 * @param outputDirectory 输出文件目录
 */
ConversionThread::ConversionThread(CAJ2PDF *parent,
                                   QString inputFilePath,
                                   std::string outputDirectory)
    : QThread(parent) {
  this->instance = parent;
  this->inputFilePath = inputFilePath;
  this->outputDirectory = outputDirectory;
}

/**
 * @brief 开始转换
 *
 * 该方法将会在调用 start() 后执行
 *
 */
void ConversionThread::run() {
  // 设置此二进制可执行文件所在的目录，用来定位 /external 目录
  QString currentDir = QCoreApplication::applicationDirPath();
  // caj2pdf 和 mutool 的路径
  QString caj2pdfExecutablePath =
      QDir(QDir(currentDir).filePath(tr("external"))).filePath(tr("caj2pdf"));
  QString mutoolExecutablePath =
      QDir(QDir(currentDir).filePath(tr("external"))).filePath(tr("mutool"));
  // 从 inputFilePath 这个文件绝对路径获得输入文件的文件名（含扩展名）
  std::string inputFileName = inputFilePath.toStdString().substr(
      inputFilePath.toStdString().find_last_of("/\\") + 1);
  // 输出文件的文件名。将输入文件的扩展名替换成 .pdf
  std::string outputFileName =
      inputFileName.substr(0, inputFileName.find_last_of(".")) + ".pdf";
  // 输出文件的绝对路径
  QString outputFile = QDir(QString::fromStdString(outputDirectory))
                           .filePath(QString::fromStdString(outputFileName));
  // 执行命令，成功返回 0
  QProcess process;
  QStringList args = {QString::fromUtf8("convert"), inputFilePath,
                      QString::fromUtf8("-o"),      outputFile,
                      QString::fromUtf8("-m"),      mutoolExecutablePath};
  // 开始执行命令，转换完成后发送信号，根据转换结果更新第三页的页面
  emit conversionFinished(process.execute(caj2pdfExecutablePath, args) == 0,
                          inputFilePath);
}
