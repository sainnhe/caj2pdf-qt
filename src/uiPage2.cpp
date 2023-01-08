// -----------------------------------------------------------------------------
// Name:           CAJ2PDF Qt
// Description:    CAJ 转 PDF 转换器
// Author:         Sainnhe Park <i@sainnhe.dev>
// Website:        https://caj2pdf-qt.sainnhe.dev
// License:        GPL3
// -----------------------------------------------------------------------------

#include "caj2pdf.hpp"

/**
 * @brief 第二页的 UI
 *
 * @param {name}
 */
void CAJ2PDF::uiPage2(void) {
  page2 = new QWidget(this);
  selectOutputLabel = new QLabel(tr("选择输出目录："), page2);
  selectOutputLineEdit = new QLineEdit(page2);
  selectOutputButton = new QPushButton(tr("..."), page2);
  outputTextBrowser = new QTextBrowser(page2);
  outputTextBrowser->setMinimumWidth(500);
  page2CancelButton = new QPushButton(tr("取消"), page2);
  page2PrevButton = new QPushButton(tr("上一步"), page2);
  page2NextButton = new QPushButton(tr("下一步"), page2);
  page2TopLayout = new QHBoxLayout();
  page2TopLayout->addWidget(selectOutputLabel);
  page2TopLayout->addWidget(selectOutputLineEdit);
  page2TopLayout->addWidget(selectOutputButton, 0, Qt::AlignRight);
  page2MiddleLayout = new QHBoxLayout();
  page2MiddleLayout->addWidget(outputTextBrowser);
  page2BottomLayout = new QHBoxLayout();
  page2BottomLayout->addWidget(page2CancelButton, 2, Qt::AlignRight);
  page2BottomLayout->addWidget(page2PrevButton, 0, Qt::AlignRight);
  page2BottomLayout->addWidget(page2NextButton, 0, Qt::AlignRight);
  page2MainLayout = new QVBoxLayout(page2);
  page2MainLayout->addLayout(page2TopLayout);
  page2MainLayout->addLayout(page2MiddleLayout);
  page2MainLayout->addLayout(page2BottomLayout);
  connect(selectOutputButton, SIGNAL(clicked()), this,
          SLOT(handlePage2SelectOutputButton()));
  connect(page2PrevButton, SIGNAL(clicked()), this,
          SLOT(handlePage2PrevButton()));
  connect(page2CancelButton, SIGNAL(clicked()), this,
          SLOT(handleCancelButton()));
  connect(page2NextButton, SIGNAL(clicked()), this,
          SLOT(handlePage2NextButton()));
}
