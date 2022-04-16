// -----------------------------------------------------------------------------
// Name:           CAJ2PDF Qt
// Description:    CAJ 转 PDF 转换器
// Author:         Sainnhe Park <sainnhe@gmail.com>
// Website:        https://caj2pdf-qt.sainnhe.dev
// License:        GPL3
// -----------------------------------------------------------------------------

#include "caj2pdf.h"

/**
 * @brief 总体 UI
 *
 * @param {name}
 */
void CAJ2PDF::uiMain(void) {
  navigationList = new QListWidget(this);
  item1 = new QListWidgetItem(tr("输入文件"), navigationList);
  item1->setTextAlignment(Qt::AlignCenter);
  item2 = new QListWidgetItem(tr("输出目录"), navigationList);
  item2->setTextAlignment(Qt::AlignCenter);
  item3 = new QListWidgetItem(tr("开始转换"), navigationList);
  item3->setTextAlignment(Qt::AlignCenter);
  navigationList->setCurrentRow(0);
  for (int index = 1; index <= 2; index++) {
    navigationList->item(index)->setFlags(
        navigationList->item(index)->flags().setFlag(Qt::ItemIsEnabled, false));
  }
  stack = new QStackedWidget(this);
  stack->addWidget(page1);
  stack->addWidget(page2);
  stack->addWidget(page3);
  mainLayout = new QHBoxLayout(this);
  mainLayout->setSpacing(5);
  mainLayout->setContentsMargins(5, 5, 5, 5);
  mainLayout->addWidget(navigationList);
  mainLayout->addWidget(stack, 0, Qt::AlignHCenter);
  mainLayout->setStretchFactor(navigationList, 1);
  mainLayout->setStretchFactor(stack, 3);
  connect(navigationList, SIGNAL(currentRowChanged(int)), stack,
          SLOT(setCurrentIndex(int)));
}
