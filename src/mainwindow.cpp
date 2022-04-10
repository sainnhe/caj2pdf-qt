// -----------------------------------------------------------------------------
// Name:           CAJ2PDF Qt
// Description:    CAJ 转 PDF 转换器
// Author:         Aymeric <343894011@qq.com>
// Website:        https://caj2pdf-qt.sainnhe.dev
// License:        GPL3
// -----------------------------------------------------------------------------
#include "mainwindow.h"

#include <QToolButton>
#include <QPushButton>
#include "qssreader.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <string>
#include <QFuture>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QtConcurrent/QtConcurrentRun>

#define INPUT_PAGE 1
#define OUTPUT_PAGE 2
#define RESULT_PAGR 3

MainWindow::MainWindow(QWidget* parent) :
    CFramelessWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    version = "0.1.3 beauty";
    initialization();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialization()
{
    setResizeableAreaWidth(8);
    setTitleBar(ui->topWidget);

    initUI();

    this->setAcceptDrops(true);

    // 设置此二进制可执行文件所在的目录，用来定位 /external 目录
    currentDir = QCoreApplication::applicationDirPath();
    convertStatus = statusNotStarted;                                   // 设置转换状态
    curIndex = 1;
    btnGrp = new QButtonGroup(this);
    btnGrp->addButton(ui->btnInputfile);
    btnGrp->addButton(ui->btnOutputfile);
    btnGrp->addButton(ui->btnResult);
    btnGrp->setExclusive(true);

    // 根据操作系统的不同设置编码方式
    if (!QString::compare(QSysInfo::kernelType(), tr("winnt"))) {
        codecType = "GB2312";
    }
    else {
        codecType = "UTF-8";
    }

    bool ok = QssReader::setCSS(this, QString(":/css/mainwindow.css"));
    if (false == ok) {
        qDebug() << "Load css file failed.";
    }

    connect(ui->btnTopMini, &QToolButton::released, this, &MainWindow::slot_miniWindow);
    connect(ui->btnTopMax, &QToolButton::released, this, &MainWindow::slot_maxWindow);
    connect(ui->btnTopClose, &QToolButton::released, this, &MainWindow::slot_closeWindow);

    connect(ui->btnChoose, &QPushButton::released, this, &MainWindow::slot_selectInputOutput);
    connect(ui->btnPre, &QPushButton::released, this, &MainWindow::slot_preButton);
    connect(ui->btnNext, &QPushButton::released, this, &MainWindow::slot_nextAndFinish);

    connect(this, &MainWindow::signal_curIndexChanged, this, &MainWindow::slot_curIndexChanged);

    connect(ui->btnAboutthis, &QPushButton::released, this, &MainWindow::slot_openWhatIsThis);
    connect(ui->btnInputfile, &QPushButton::released, this, &MainWindow::slot_openWhatIsThis);
    connect(ui->btnOutputfile, &QPushButton::released, this, &MainWindow::slot_openWhatIsThis);
    connect(ui->btnResult, &QPushButton::released, this, &MainWindow::slot_openWhatIsThis);

}

void MainWindow::initUI()
{
    ui->progressBar->setVisible(false);

    ui->labelTopTitle->setText(tr("CAJ转PDF 美化版"));

    ui->lineEditUrl->setPlaceholderText(tr("点按右侧按钮选择文件..."));

    ui->btnInputfile->setText(tr("输入文件"));
    ui->btnOutputfile->setText(tr("输出目录"));
    ui->btnResult->setText(tr("转换结果"));

    ui->btnOutputfile->setDisabled(true);
    ui->btnResult->setDisabled(true);

    ui->btnChoose->setText(tr("选择文件"));
    ui->btnPre->setText(tr("上一步"));
    ui->btnNext->setText(tr("下一步"));

    ui->btnPre->setVisible(false);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (statusConverting == convertStatus) {
        QMessageBox::warning(this, "警告", "当前正在转换，不允许退出！");
    }
    else {
        close();
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
    if (true)
        event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent* event)
{
    //获取文件路径 (QString)
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()) return;
    foreach (auto i, urls) {
        if (!i.toLocalFile().contains(".caj")) {
            qDebug("不支持的文件类型");
            ui->textBrowserResult->append(tr("不支持的文件类型: ") + i.toLocalFile());
            continue;
        }
        else {
            inputFiles.append(i.toLocalFile());
            ui->textBrowserResult->append(i.toLocalFile());
        }
    }
}

void MainWindow::slot_miniWindow()
{
    showMinimized();
}

void MainWindow::slot_maxWindow()
{
    if (isMaximized())
        showNormal();
    else showMaximized();
}

void MainWindow::slot_closeWindow()
{
    close();
}

void MainWindow::slot_cancle()
{

}

void MainWindow::slot_curIndexChanged(int index)
{
    switch (index) {
    case 1: {
        // 选择输入文件界面，仅显示选择文件和下一步
        // 隐藏进度条和上一步
        ui->btnInputfile->setChecked(true);
        ui->progressBar->setVisible(false);
        ui->btnPre->setVisible(false);
        ui->btnChoose->setVisible(true);

        ui->btnChoose->setText(tr("选择文件"));
        ui->btnNext->setText(tr("下一步"));

        ui->lineEditUrl->setVisible(true);
        ui->progressBar->setVisible(false);

        ui->btnInputfile->setDisabled(false);
        ui->btnOutputfile->setDisabled(true);
        ui->btnResult->setDisabled(true);
        break;
    }
    case 2: {
        // 选择输出目录界面，显示选择目录和上一步
        // 隐藏进度条和上一步
        ui->btnOutputfile->setChecked(true);
        ui->btnChoose->setText(tr("选择目录"));
        ui->btnPre->setVisible(true);

        ui->btnInputfile->setDisabled(true);
        ui->btnOutputfile->setDisabled(false);
        ui->btnResult->setDisabled(true);
        break;
    }
    case 3: {
        // 展示输出结果界面，显示进度条和完成按钮
        // 隐藏目录和上一步
        ui->btnNext->setText(tr("返回"));
        ui->btnNext->setDisabled(true);
        ui->btnPre->setVisible(false);
        ui->btnChoose->setVisible(false);
        ui->lineEditUrl->setVisible(false);
        ui->progressBar->setVisible(true);

        ui->btnResult->setChecked(true);
        ui->btnInputfile->setDisabled(true);
        ui->btnOutputfile->setDisabled(true);
        ui->btnResult->setDisabled(false);
        break;
    }
    }
}

void MainWindow::slot_preButton()
{
    emit signal_curIndexChanged(1);
}

void MainWindow::slot_openWhatIsThis()
{
    QMessageBox::information(this, tr("关于"),
                             tr(std::string("<h2 align=\"center\">关于本项目</h2><br><p style=\"line-height:150%\">"
                                            "这是一个免费开源的 CAJ 转 PDF 转换器，基于 <a href=\"https://github.com/caj2pdf/caj2pdf\">cajpdf</a> 和 <a href=\"https://mupdf.com/\">mupdf</a> 实现。"
                                            "由 Aymeric 美化。"
                                            "<br>主页：<a href=\"https://caj2pdf-qt.sainnhe.dev\">https://caj2pdf-qt.sainnhe.dev</a>"
                                            "<br>作者：<a href=\"mailto:sainnhe@gmail.com\">Sainnhe Park</a>"
                                            "<br>美化：<a href=\"mailto:343894011@qq.com\">Aymeric</a> (如有 Bug 请发邮件反馈)"
                                            "<br>许可：GPL3<br>版本："
                                            + version + "</p>").c_str()));
}

/**
 * @brief 第一页的选择输入文件按钮
 *
 * 打开一个文件选择窗口，选择一个或多个 CAJ 文件，将结果放入 inputFiles ；
 *
 * 将这些文件的绝对路径写入 inputTextBrowser 和 outputTextBrowser 。
 *
 */
void MainWindow::slot_selectInputOutput()
{
    if (1 == curIndex) {
        inputFiles = QFileDialog::getOpenFileNames(this,
                     tr("打开 CAJ 文件"), QDir::homePath(), tr("CAJ 文件 (*.caj)"));
        QString inputFilesText = tr("");
        for (const QString& str : inputFiles) {
            inputFilesText = inputFilesText + str + "\n";
        }
        ui->lineEditUrl->setText(inputFilesText);
        ui->textBrowserResult->append(tr("已选择文件: "));
        ui->textBrowserResult->append(inputFilesText);
    }
    else if (2 == curIndex) {
        outputDirectory = QFileDialog::getExistingDirectory(this,
                          tr("选择目录"),
                          ui->lineEditUrl->text(),
                          QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks).toStdString();
        ui->lineEditUrl->setText(QString::fromStdString(outputDirectory));
    }
}

/**
 * @brief 第一页的下一步按钮
 *
 * 如果未选择任何文件，则弹出一个警告框并返回；
 *
 * 否则更新 stack 和 navigationList, 切换到下一页；
 *
 * 将第一个输入文件所在目录设置为默认输出目录。
 *
 */
void MainWindow::slot_nextAndFinish()
{
    switch (curIndex) {
    case 1: {
        if (inputFiles.empty()) {
            QMessageBox::warning(this, tr("警告"), tr("未选择 CAJ 文件"));
            return;
        }

        std::string defaultDir = QFileInfo(inputFiles[0]).absoluteDir().absolutePath().toStdString();
        ui->lineEditUrl->setText(QString::fromStdString(defaultDir));

        curIndex = OUTPUT_PAGE;
        emit signal_curIndexChanged(OUTPUT_PAGE);
        break;
    }
    case 2: {
        if (convertStatus == statusNotStarted) {
            if (!QDir(ui->lineEditUrl->text()).exists()) {
                QMessageBox::warning(this, tr("警告"), tr("请选择一个存在的目录"));
                return;
            }
            outputDirectory = ui->lineEditUrl->text().toStdString();
            ui->progressBar->setRange(0, inputFiles.size());
            ui->progressBar->setValue(0);
            QFuture<void> future = QtConcurrent::run(convert, this);
        }

        curIndex = RESULT_PAGR;
        emit signal_curIndexChanged(RESULT_PAGR);
        break;
    }
    case 3: {
        curIndex = INPUT_PAGE;
        emit signal_curIndexChanged(INPUT_PAGE);
        break;
    }
    default:
        qDebug() << tr("怎么可能有这个代码？？");
    }
}
