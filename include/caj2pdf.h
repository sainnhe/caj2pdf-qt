// -----------------------------------------------------------------------------
// Name:           CAJ2PDF Qt
// Description:    CAJ 转 PDF 转换器
// Author:         Sainnhe Park <sainnhe@gmail.com>
// Website:        https://caj2pdf-qt.sainnhe.dev
// License:        GPL3
// -----------------------------------------------------------------------------

#ifndef CAJ2PDF_H
#define CAJ2PDF_H

#include <QApplication>
#include <QDialog>
#include <QMessageBox>
#include <QListWidget>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QTextBrowser>
#include <QProgressBar>
#include <QFuture>
#include <QtConcurrent/QtConcurrentRun>
#include <QTextCodec>
#include <QSysInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class CAJ2PDF; }
QT_END_NAMESPACE

// 转换状态
enum ConvertStatus {
    statusNotStarted,   // 尚未开始
    statusConverting,   // 正在转换
    statusFinished      // 转换完成
};

class CAJ2PDF : public QDialog
{
    Q_OBJECT

public:
    CAJ2PDF(QWidget *parent = nullptr, std::string argv0 = nullptr);
    ~CAJ2PDF();
    std::string outputDirectory;    // 输出目录，默认为第一个输入文件所在的目录
    QString currentDir;             // 编译出来的可执行文件所在的目录，用来定位 /external/caj2pdf 和 /external/mutool
    ConvertStatus convertStatus;    // 转换状态，用来设置按钮的行为

    // 第三页
    QPushButton *page3NextButton;

protected:
    virtual bool eventFilter(QObject *object, QEvent *event);   // windows 下的 ？按钮触发的事件

private slots:
    // 总体
    void handleCancelButton();

    // 第一页
    void handlePage1SelectInputButton();
    void handlePage1NextButton();

    // 第二页
    void handlePage2SelectOutputButton();
    void handlePage2PrevButton();
    void handlePage2NextButton();

    // 第三页
    void updatePage3UI(int returnCode, std::string inputFile);
    void handlePage3PrevButton();
    void handlePage3NextButton();

private:
    std::string version;
    Ui::CAJ2PDF *ui;
    static void convert(CAJ2PDF *instance);
    void handleWhatsThisEntry();    // windows 下的 ？按钮所调用的函数

    // 第一页
    QWidget *page1;
    QLabel *selectInputLabel;
    QPushButton *selectInputButton;
    QList<QString> inputFiles;
    QTextBrowser *inputTextBrowser;
    QPushButton *page1CancelButton;
    QPushButton *page1NextButton;
    QHBoxLayout *page1TopLayout;
    QHBoxLayout *page1MiddleLayout;
    QHBoxLayout *page1BottomLayout;
    QVBoxLayout *page1MainLayout;

    // 第二页
    QWidget *page2;
    QLabel *selectOutputLabel;
    QLineEdit *selectOutputLineEdit;
    QPushButton *selectOutputButton;
    QTextBrowser *outputTextBrowser;
    QPushButton *page2CancelButton;
    QPushButton *page2PrevButton;
    QPushButton *page2NextButton;
    QHBoxLayout *page2TopLayout;
    QHBoxLayout *page2MiddleLayout;
    QHBoxLayout *page2BottomLayout;
    QVBoxLayout *page2MainLayout;

    // 第三页
    QWidget *page3;
    QLabel *progressLabel;
    QProgressBar *progressBar;
    QTextBrowser *statusTextBrowser;
    QPushButton *page3CancelButton;
    QPushButton *page3PrevButton;
    QHBoxLayout *page3TopLayout;
    QHBoxLayout *page3MiddleLayout;
    QHBoxLayout *page3BottomLayout;
    QVBoxLayout *page3MainLayout;

    // 总体
    QListWidget *navigationList;
    QListWidgetItem *item1;
    QListWidgetItem *item2;
    QListWidgetItem *item3;
    QStackedWidget *stack;
    QHBoxLayout *mainLayout;
};

// 定义一个 Convert 类，在 CAJ2PDF 对象中通过异步来转换文件以防止界面卡顿
// Convert 对象的转换结果通过 signals && slots 来和 CAJ2PDF 对象进行交互，以更新 page3 的界面
class Convert : public QObject {
    Q_OBJECT

public:
    explicit Convert(QObject *parent = 0) : QObject(parent) {}
    void handleConvert(CAJ2PDF *instance, QString inputFileRaw);

signals:
    void requestUpdateUI(int returnCode, std::string inputFile);
};

#endif // CAJ2PDF_H
