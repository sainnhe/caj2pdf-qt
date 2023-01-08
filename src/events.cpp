// -----------------------------------------------------------------------------
// Name:           CAJ2PDF Qt
// Description:    CAJ 转 PDF 转换器
// Author:         Sainnhe Park <i@sainnhe.dev>
// Website:        https://caj2pdf-qt.sainnhe.dev
// License:        GPL3
// -----------------------------------------------------------------------------

#include "caj2pdf.hpp"

/**
 * @brief 若筛选出 EnterWhatsThisMode 事件，则执行 handleWhatsThisEntry()
 *
 * @param object 待筛选的对象
 * @param event 待筛选的事件
 * @return 筛选是否成功
 */
bool CAJ2PDF::eventFilter(QObject *object, QEvent *event) {
  if (event->type() == QEvent::EnterWhatsThisMode) {
    // 弹出一个关于本项目信息的消息框
    QMessageBox::information(
        this, QString::fromUtf8("关于"),
        QString::fromUtf8(
            std::string(
                "<h2 align=\"center\">关于本项目</h2><br><p style=\"line-height:150%\">这是一个免费开源的 CAJ 转 PDF 转换器，基于 <a href=\"https://github.com/caj2pdf/caj2pdf\">cajpdf</a> 和 <a href=\"https://mupdf.com/\">mupdf</a> 实现。<br>主页：<a href=\"https://caj2pdf-qt.sainnhe.dev\">https://caj2pdf-qt.sainnhe.dev</a><br>作者：<a href=\"mailto:i@sainnhe.dev\">Sainnhe Park</a><br>许可：<a href=\"https://github.com/sainnhe/caj2pdf-qt/blob/master/LICENSE\">GPL3</a><br>版本：<a href=\"https://caj2pdf-qt.sainnhe.dev/CHANGELOG.html\">" +
                version + "</a></p>")
                .c_str()));
    return true;
  }
  return QObject::eventFilter(object, event);
}

/**
 * @brief 设置 dragEnterEvent
 *
 * 当拖拽的数据含有 Urls 且处于第一页的时候接受该事件
 *
 * @param event 事件
 */
void CAJ2PDF::dragEnterEvent(QDragEnterEvent *event) {
  if (event->mimeData()->hasUrls() && stack->currentIndex() == 0) {
    event->accept();
  }
}

/**
 * @brief 设置 dropEvent
 *
 * 将 *.caj 文件添加到 inputFiles 中
 *
 * @param event 事件
 */
void CAJ2PDF::dropEvent(QDropEvent *event) {
  const QMimeData *mimeData = event->mimeData();
  QList<QUrl> urlList = mimeData->urls();
  // 添加新文件
  for (int i = 0; i < urlList.size() && i < 32; i++) {
    if (urlList.at(i).toLocalFile().endsWith(tr(".caj"))) {
      inputFiles += urlList.at(i).toLocalFile();
    }
  }
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
