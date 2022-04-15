// -----------------------------------------------------------------------------
// Name:           CAJ2PDF Qt
// Description:    CAJ 转 PDF 转换器
// Author:         Sainnhe Park <sainnhe@gmail.com>
// Website:        https://caj2pdf-qt.sainnhe.dev
// License:        GPL3
// -----------------------------------------------------------------------------

#include <QDir>

#include "caj2pdf.h"

#ifdef _WIN32
// 在 windows 下引入这个头文件，这是为了使用 WinExec() 和 SW_HIDE
#include <windows.h>
#else
// 为了让编译通过，瞎写一些定义。
// 这些东西实际上用不到
#define SW_HIDE "none"
int WinExec(bool a, std::string b) { return 0; }
#endif

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
 * @param inputFileRaw 未转码的输入文件名
 */
void Convert::handleConvert(CAJ2PDF *instance, QString inputFileRaw) {
  // 根据操作系统的不同确定编码类型，用来解决 Windows 下的中文路径问题
  std::string codecType;
  if (!QString::compare(QSysInfo::kernelType(), tr("winnt"))) {
    codecType = "GB2312";
  } else {
    codecType = "UTF-8";
  }
  // 根据 codecType 实例化一个转码对象
  QTextCodec *codec = QTextCodec::codecForName(codecType.c_str());
  // inputFile 为转码后的文件名
  std::string inputFile = codec->fromUnicode(inputFileRaw).data();
  // caj2pdf 和 mutool 的路径（转码前）
  QString caj2pdfExecutablePathRaw =
      QDir(QDir(instance->currentDir).filePath(tr("external")))
          .filePath(tr("caj2pdf"));
  QString mutoolExecutablePathRaw =
      QDir(QDir(instance->currentDir).filePath(tr("external")))
          .filePath(tr("mutool"));
  // caj2pdf 和 mutool 的路径（转码后）
  std::string caj2pdfExecutablePath =
      codec->fromUnicode(caj2pdfExecutablePathRaw).data();
  std::string mutoolExecutablePath =
      codec->fromUnicode(mutoolExecutablePathRaw).data();
  // 从 inputFileRaw 这个文件绝对路径获得输入文件的文件名（含扩展名）
  std::string inputFileName = inputFileRaw.toStdString().substr(
      inputFileRaw.toStdString().find_last_of("/\\") + 1);
  // 输出文件的文件名。将输入文件的扩展名替换成 .pdf
  std::string outputFileName =
      inputFileName.substr(0, inputFileName.find_last_of(".")) + ".pdf";
  // 输出文件的绝对路径（转码前）
  QString outputFileRaw =
      QDir(QString::fromStdString(instance->outputDirectory))
          .filePath(QString::fromStdString(outputFileName));
  // 输出文件的绝对路径（转码后）
  std::string outputFile = codec->fromUnicode(outputFileRaw).data();
  // 在 Windows 下用 WinExec 执行命令，否则会弹出命令行黑框
  if (!QString::compare(QSysInfo::kernelType(), tr("winnt"))) {
    // 执行命令，成功返回 > 31
    emit requestUpdateUI(WinExec((caj2pdfExecutablePath + " convert \"" +
                                  inputFile + "\" -o \"" + outputFile +
                                  "\" -m \"" + mutoolExecutablePath + "\"")
                                     .c_str(),
                                 SW_HIDE) <= 31,
                         inputFileRaw.toStdString());
  } else {
    // 执行命令，成功返回 0
    emit requestUpdateUI(
        system((caj2pdfExecutablePath + " convert \"" + inputFile + "\" -o \"" +
                outputFile + "\" -m \"" + mutoolExecutablePath + "\"")
                   .c_str()),
        inputFileRaw.toStdString());
  }
}
