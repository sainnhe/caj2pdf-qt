// -----------------------------------------------------------------------------
// Name:           CAJ2PDF Qt
// Description:    CAJ 转 PDF 转换器
// Author:         Sainnhe Park <i@sainnhe.dev>
// Website:        https://caj2pdf-qt.sainnhe.dev
// License:        GPL3
// -----------------------------------------------------------------------------

#include "caj2pdf.hpp"

/**
 * @brief 执行线程的构造函数
 *
 * @param parent 线程的父对象
 * @param inputFiles 输入文件列表
 * @param outputDirectory 输出文件目录
 */
ExecutionThread::ExecutionThread(CAJ2PDF *parent, QList<QString> inputFiles,
                                 std::string outputDirectory)
    : QThread(parent) {
  this->instance = parent;
  this->inputFiles = inputFiles;
  this->outputDirectory = outputDirectory;
}

/**
 * @brief 开始执行
 *
 * 该方法将会在调用 start() 后执行
 *
 */
void ExecutionThread::run() {
  int threadCount = QThread::
      idealThreadCount();  // 当前计算机的处理器核心数，包含了物理核心和逻辑核心
  std::queue<ConversionThread *> conversionThreads;  // 转换线程队列
  instance->convertStatus = statusConverting;  // 设置转换状态为正在转换
  for (QString inputFile : inputFiles) {       // 遍历所有输入文件
    // 检查当前线程数是否已达最大线程数
    // 如果是的话就等待队首线程执行完毕再继续
    while (conversionThreads.size() >= threadCount) {
      conversionThreads.front()->wait();
      conversionThreads.pop();
    }
    // 创建一个转换线程
    ConversionThread *conversionThread =
        new ConversionThread(this, instance, inputFile, outputDirectory);
    // 将该线程加入队列
    conversionThreads.push(conversionThread);
    // 连接信号槽
    connect(conversionThread, SIGNAL(conversionFinished(bool, QString)),
            instance, SLOT(updatePage3Progress(bool, QString)));
    // 开始运行转换线程
    conversionThread->start();
  }
  // 等待队列中所有线程执行完毕
  while (!conversionThreads.empty()) {
    conversionThreads.front()->wait();
    conversionThreads.pop();
  }
  // 发送线程结束信号
  emit finished();
}
