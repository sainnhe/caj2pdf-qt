// -----------------------------------------------------------------------------
// Name:           CAJ2PDF Qt
// Description:    CAJ 转 PDF 转换器
// Author:         Sainnhe Park <i@sainnhe.dev>
// Website:        https://caj2pdf-qt.sainnhe.dev
// License:        GPL3
// -----------------------------------------------------------------------------

#include "caj2pdf.hpp"

/**
 * @brief 第三页的 UI
 *
 * @param {name}
 */
void CAJ2PDF::uiPage3(void) {
  page3 = new QWidget(this);
  progressLabel = new QLabel(tr("转换进度："), page3);
  progressBar = new QProgressBar(page3);
  statusTextBrowser = new QTextBrowser(page3);
  statusTextBrowser->setMinimumWidth(500);
  page3CancelButton = new QPushButton(tr("取消"), page3);
  page3PrevButton = new QPushButton(tr("上一步"), page3);
  page3NextButton = new QPushButton(tr("完成"), page3);
  page3NextButton->setDisabled(true);
  page3TopLayout = new QHBoxLayout();
  page3TopLayout->addWidget(progressLabel, 0, Qt::AlignLeft);
  page3TopLayout->addWidget(progressBar);
  page3TopLayout->setContentsMargins(0, 10, 0, 10);
  page3MiddleLayout = new QHBoxLayout();
  page3MiddleLayout->addWidget(statusTextBrowser);
  page3BottomLayout = new QHBoxLayout();
  page3BottomLayout->addWidget(page3CancelButton, 2, Qt::AlignRight);
  page3BottomLayout->addWidget(page3PrevButton, 0, Qt::AlignRight);
  page3BottomLayout->addWidget(page3NextButton, 0, Qt::AlignRight);
  page3MainLayout = new QVBoxLayout(page3);
  page3MainLayout->addLayout(page3TopLayout);
  page3MainLayout->addLayout(page3MiddleLayout);
  page3MainLayout->addLayout(page3BottomLayout);
  connect(page3PrevButton, SIGNAL(clicked()), this,
          SLOT(handlePage3PrevButton()));
  connect(page3CancelButton, SIGNAL(clicked()), this,
          SLOT(handleCancelButton()));
  connect(page3NextButton, SIGNAL(clicked()), this,
          SLOT(handlePage3NextButton()));
  mutex = new QMutex();
}
