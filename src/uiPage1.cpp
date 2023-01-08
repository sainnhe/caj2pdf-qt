// -----------------------------------------------------------------------------
// Name:           CAJ2PDF Qt
// Description:    CAJ 转 PDF 转换器
// Author:         Sainnhe Park <i@sainnhe.dev>
// Website:        https://caj2pdf-qt.sainnhe.dev
// License:        GPL3
// -----------------------------------------------------------------------------

#include "caj2pdf.hpp"

/**
 * @brief 第一页的 UI
 *
 * @param {name}
 */
void CAJ2PDF::uiPage1(void) {
  page1 = new QWidget(this);
  selectInputLabel = new QLabel(tr("选择输入文件："), page1);
  selectInputButton = new QPushButton(tr("选择"), page1);
  inputTextBrowser = new QTextBrowser(page1);
  inputTextBrowser->setMinimumWidth(500);
  page1CancelButton = new QPushButton(tr("取消"), page1);
  page1NextButton = new QPushButton(tr("下一步"), page1);
  page1TopLayout = new QHBoxLayout();
  page1TopLayout->addWidget(selectInputLabel, 0, Qt::AlignLeft);
  page1TopLayout->addWidget(selectInputButton, 0, Qt::AlignRight);
  page1MiddleLayout = new QHBoxLayout();
  page1MiddleLayout->addWidget(inputTextBrowser);
  page1BottomLayout = new QHBoxLayout();
  page1BottomLayout->addWidget(page1CancelButton, 2, Qt::AlignRight);
  page1BottomLayout->addWidget(page1NextButton, 0, Qt::AlignRight);
  page1MainLayout = new QVBoxLayout(page1);
  page1MainLayout->addLayout(page1TopLayout);
  page1MainLayout->addLayout(page1MiddleLayout);
  page1MainLayout->addLayout(page1BottomLayout);
  connect(selectInputButton, SIGNAL(clicked()), this,
          SLOT(handlePage1SelectInputButton()));
  connect(page1CancelButton, SIGNAL(clicked()), this,
          SLOT(handleCancelButton()));
  connect(page1NextButton, SIGNAL(clicked()), this,
          SLOT(handlePage1NextButton()));
}
