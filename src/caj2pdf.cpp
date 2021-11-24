// -----------------------------------------------------------------------------
// Name:           CAJ2PDF Qt
// Description:    CAJ 转 PDF 转换器
// Author:         Sainnhe Park <sainnhe@gmail.com>
// Website:        https://caj2pdf-qt.sainnhe.dev
// License:        GPL3
// -----------------------------------------------------------------------------

#include "caj2pdf.h"
#include "./ui_caj2pdf.h"

CAJ2PDF::CAJ2PDF(QWidget *parent, std::string argv0)
    : QDialog(parent)
    , ui(new Ui::CAJ2PDF) {
    version = "0.1.1";
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::WindowContextHelpButtonHint);    // 启用窗口右上角的 ？按钮
    qApp->installEventFilter(this);     // 安装事件
    currentPath = argv0;                // 设置此二进制可执行文件的路径，用来定位 /external 目录
    convertStatus = statusNotStarted;   // 设置转换状态
    // 根据操作系统的不同设置编码方式
    if (!QString::compare(QSysInfo::kernelType(), tr("winnt"))) {
        codecType = "GB2312";
    } else {
        codecType = "UTF-8";
    }

    // 第一页
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
    connect(selectInputButton, SIGNAL(clicked()), this, SLOT(handlePage1SelectInputButton()));
    connect(page1CancelButton, SIGNAL(clicked()), this, SLOT(handleCancelButton()));
    connect(page1NextButton, SIGNAL(clicked()), this, SLOT(handlePage1NextButton()));

    // 第二页
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
    connect(selectOutputButton, SIGNAL(clicked()), this, SLOT(handlePage2SelectOutputButton()));
    connect(page2PrevButton, SIGNAL(clicked()), this, SLOT(handlePage2PrevButton()));
    connect(page2CancelButton, SIGNAL(clicked()), this, SLOT(handleCancelButton()));
    connect(page2NextButton, SIGNAL(clicked()), this, SLOT(handlePage2NextButton()));

    // 第三页
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
    connect(page3PrevButton, SIGNAL(clicked()), this, SLOT(handlePage3PrevButton()));
    connect(page3CancelButton, SIGNAL(clicked()), this, SLOT(handleCancelButton()));
    connect(page3NextButton, SIGNAL(clicked()), this, SLOT(handlePage3NextButton()));

    // 总体
    navigationList = new QListWidget(this);
    item1 = new QListWidgetItem(tr("输入文件"), navigationList);
    item1->setTextAlignment(Qt::AlignCenter);
    item2 = new QListWidgetItem(tr("输出目录"), navigationList);
    item2->setTextAlignment(Qt::AlignCenter);
    item3 = new QListWidgetItem(tr("开始转换"), navigationList);
    item3->setTextAlignment(Qt::AlignCenter);
    navigationList->setCurrentRow(0);
    for(int index = 1; index <= 2; index++) {
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
    connect(navigationList, SIGNAL(currentRowChanged(int)), stack, SLOT(setCurrentIndex(int)));
}

CAJ2PDF::~CAJ2PDF() {
    delete ui;
}

/**
 * @brief 处理取消按钮
 *
 * 若正在转换中，则弹出消息框询问是否确定结束程序；
 *
 * 否则直接结束程序。
 *
 */
void CAJ2PDF::handleCancelButton() {
    if (convertStatus == statusNotStarted || convertStatus == statusFinished) {
        QApplication::quit();
    } else {
        switch (QMessageBox::question(this, tr("警告"),
                    tr("转换尚未完成，是否要结束程序？"),
                    QMessageBox::Ok|QMessageBox::Cancel, QMessageBox::Ok)) {
            case QMessageBox::Ok:
                QApplication::quit();
                break;
            case QMessageBox::Cancel:
                break;
            default:
                break;
        }
    }
}

/**
 * @brief 若筛选出 EnterWhatsThisMode 事件，则执行 handleWhatsThisEntry()
 *
 * @param object 待筛选的对象
 * @param event 待筛选的事件
 * @return 筛选是否成功
 */
bool CAJ2PDF::eventFilter(QObject *object, QEvent *event) {
    if (event->type() == QEvent::EnterWhatsThisMode) {
        handleWhatsThisEntry();
        return true;
    }
    return QObject::eventFilter(object, event);
}

/**
 * @brief 弹出一个关于本项目信息的消息框
 *
 */
void CAJ2PDF::handleWhatsThisEntry() {
    QMessageBox::information(this, tr("关于"), tr(std::string("<h2 align=\"center\">关于本项目</h2><br><p style=\"line-height:150%\">这是一个免费开源的 CAJ 转 PDF 转换器，基于 <a href=\"https://github.com/caj2pdf/caj2pdf\">cajpdf</a> 和 <a href=\"https://mupdf.com/\">mupdf</a> 实现。<br>主页：<a href=\"https://caj2pdf-qt.sainnhe.dev\">https://caj2pdf-qt.sainnhe.dev</a><br>作者：<a href=\"mailto:sainnhe@gmail.com\">Sainnhe Park</a><br>许可：GPL3<br>版本：" + version + "</p>").c_str()));
}
