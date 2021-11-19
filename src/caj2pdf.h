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

enum ConvertStatus {
    statusNotStarted,
    statusConverting,
    statusFinished
};

class CAJ2PDF : public QDialog
{
    Q_OBJECT

public:
    CAJ2PDF(QWidget *parent = nullptr, std::string argv0 = nullptr);
    ~CAJ2PDF();
    std::string outputDirectory;
    std::string currentPath;
    ConvertStatus convertStatus;
    std::string codecType;

    // 第三页
    QPushButton *page3NextButton;

protected:
    virtual bool eventFilter(QObject *object, QEvent *event);

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
    Ui::CAJ2PDF *ui;
    static void convert(CAJ2PDF *instance);
    void handleWhatsThisEntry();

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

class Convert : public QObject {
    Q_OBJECT

public:
    explicit Convert(QObject *parent = 0) : QObject(parent) {}
    void handleConvert(CAJ2PDF *instance, QString inputFileRaw);

signals:
    void requestUpdateUI(int returnCode, std::string inputFile);
};

#endif // CAJ2PDF_H
