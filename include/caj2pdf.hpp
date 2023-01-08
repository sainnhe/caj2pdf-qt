// -----------------------------------------------------------------------------
// Name:           CAJ2PDF Qt
// Description:    CAJ 转 PDF 转换器
// Author:         Sainnhe Park <i@sainnhe.dev>
// Website:        https://caj2pdf-qt.sainnhe.dev
// License:        GPL3
// -----------------------------------------------------------------------------

#ifndef CAJ2PDF_HPP
#define CAJ2PDF_HPP

#include <QApplication>
#include <QComboBox>
#include <QDialog>
#include <QDir>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QListWidget>
#include <QMessageBox>
#include <QMimeData>
#include <QMutex>
#include <QProcess>
#include <QProgressBar>
#include <QPushButton>
#include <QStackedWidget>
#include <QStringList>
#include <QSysInfo>
#include <QTextBrowser>
#include <QThread>
#include <QUrl>
#include <QVBoxLayout>
#include <QVector>
#include <queue>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui {
class CAJ2PDF;
}
QT_END_NAMESPACE

// 转换状态
enum ConvertStatus {
  statusNotStarted,  // 尚未开始
  statusConverting,  // 正在转换
  statusFinished     // 转换完成
};

class CAJ2PDF : public QDialog {
  Q_OBJECT

 public:
  CAJ2PDF(QWidget *parent = nullptr, std::string argv0 = nullptr);
  ~CAJ2PDF();
  ConvertStatus convertStatus;  // 转换状态，用来设置按钮的行为

 protected:
  virtual bool eventFilter(QObject *object,
                           QEvent *event);  // Windows 下的 ？按钮触发的事件
  void dragEnterEvent(QDragEnterEvent *event);  // Drag 事件
  void dropEvent(QDropEvent *event);            // Drop 事件

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
  void handlePage3PrevButton();
  void handlePage3NextButton();
  void updatePage3Progress(bool status, QString inputFilePath);
  void updatePage3FinishedStatus();

 private:
  Ui::CAJ2PDF *ui;
  std::string version;          // 版本信息
  std::string outputDirectory;  // 输出目录，默认为第一个输入文件所在的目录

  // 第一页
  void uiPage1(void);
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
  void uiPage2(void);
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
  void uiPage3(void);
  QWidget *page3;
  QLabel *progressLabel;
  QPushButton *page3CancelButton;
  QPushButton *page3PrevButton;
  QPushButton *page3NextButton;
  QHBoxLayout *page3TopLayout;
  QHBoxLayout *page3MiddleLayout;
  QHBoxLayout *page3BottomLayout;
  QVBoxLayout *page3MainLayout;
  QProgressBar *progressBar;
  QTextBrowser *statusTextBrowser;
  QMutex *mutex;

  // 总体
  void uiMain(void);
  QListWidget *navigationList;
  QListWidgetItem *item1;
  QListWidgetItem *item2;
  QListWidgetItem *item3;
  QStackedWidget *stack;
  QHBoxLayout *mainLayout;
};

// 用于执行转换的线程
class ConversionThread : public QThread {
  Q_OBJECT

 public:
  explicit ConversionThread(QObject *parent = nullptr,
                            CAJ2PDF *instance = nullptr,
                            QString inputFilePath = "",
                            std::string outputDirectory = "");
  void run();

 signals:
  // 转换完成信号
  // status 表示转换成功与否；
  // inputFilePath 表示待转换文件的路径
  void conversionFinished(bool status, QString inputFilePath);

 private:
  CAJ2PDF *instance;
  QString inputFilePath;
  std::string outputDirectory;
};

// 用于协调转换线程的线程
class ExecutionThread : public QThread {
  Q_OBJECT

 public:
  explicit ExecutionThread(CAJ2PDF *parent = nullptr,
                           QList<QString> inputFiles = {},
                           std::string outputDirectory = "");
  void run();

 signals:
  // 所有转换线程结束的信号
  void finished();

 private:
  CAJ2PDF *instance;
  QList<QString> inputFiles;
  std::string outputDirectory;
};

#endif  // CAJ2PDF_HPP
