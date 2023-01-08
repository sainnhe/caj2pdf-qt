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
  std::queue<ConvertionThread *> convertionThreads;
  convertStatus = statusConverting;  // 设置转换状态为正在转换
  for (QString inputFile : this->inputFiles) {  // 遍历所有输入文件
    // 创建一个转换线程
    ConvertionThread *convertionThread =
        new ConvertionThread(this, inputFile, outputDirectory);
    // 将该线程加入队列
    convertionThreads.push(convertionThread);
    // 连接信号槽
    connect(convertionThread, SIGNAL(convertionFinished(bool, QString)), this,
            SLOT(updatePage3Progress(bool, QString)));
    // 开始运行转换线程
    convertionThread->start();
  }
  // 创建等待线程
  WaitingThread *waitingThread = new WaitingThread(this, convertionThreads);
  // 连接信号槽
  connect(waitingThread, SIGNAL(threadsFinished()), this,
          SLOT(updatePage3FinishedStatus()));
  // 开始等待
  waitingThread->start();
}

/**
 * @brief 转换线程的构造函数
 *
 * @param parent 线程的父对象
 * @param inputFilePath 输入文件路径
 * @param outputDirectory 输出文件目录
 */
ConvertionThread::ConvertionThread(CAJ2PDF *parent, QString inputFilePath,
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
void ConvertionThread::run() {
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
  emit convertionFinished(process.execute(caj2pdfExecutablePath, args) == 0,
                          inputFilePath);
}

/**
 * @brief 等待线程的构造函数
 *
 * @param parent 线程的父对象
 * @param convertionThreads 包含了转换线程的队列
 */
WaitingThread::WaitingThread(CAJ2PDF *parent,
                             std::queue<ConvertionThread *> convertionThreads)
    : QThread(parent) {
  this->convertionThreads = convertionThreads;
  this->instance = parent;
}

/**
 * @brief 开始等待
 *
 * 该方法将会在调用 start() 后执行
 *
 */
void WaitingThread::run() {
  // 等待队列中所有线程执行完毕
  while (!convertionThreads.empty()) {
    convertionThreads.front()->wait();
    convertionThreads.pop();
  }
  // 发送进程结束信号
  emit threadsFinished();
}
