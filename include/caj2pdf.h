// -----------------------------------------------------------------------------
// Name:           CAJ2PDF Qt
// Description:    CAJ 转 PDF 转换器
// Author:         Sainnhe Park <i@sainnhe.dev>
// Website:        https://caj2pdf-qt.sainnhe.dev
// License:        GPL3
// -----------------------------------------------------------------------------

#ifndef CAJ2PDF_H
#define CAJ2PDF_H

#include <QApplication>
#include <QComboBox>
#include <QDialog>
#include <QDir>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QFileDialog>
#include <QFuture>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QListWidget>
#include <QMessageBox>
#include <QMimeData>
#include <QProcess>
#include <QProgressBar>
#include <QPushButton>
#include <QStackedWidget>
#include <QStringList>
#include <QSysInfo>
#include <QTextBrowser>
#include <QUrl>
#include <QVBoxLayout>
#include <QVector>
#include <QtConcurrent/QtConcurrentRun>
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
  std::string outputDirectory;  // 输出目录，默认为第一个输入文件所在的目录
  QString currentDir;  // 编译出来的可执行文件所在的目录，用来定位
                       // /external/caj2pdf 和 /external/mutool
  ConvertStatus convertStatus;  // 转换状态，用来设置按钮的行为

  // 第三页
  QPushButton *page3NextButton;

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
  void updatePage3UI(int returnCode, std::string inputFile);
  void handlePage3PrevButton();
  void handlePage3NextButton();

 private:
  Ui::CAJ2PDF *ui;
  static void convert(CAJ2PDF *instance);
  std::string version;  // 版本信息

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
  QProgressBar *progressBar;
  QTextBrowser *statusTextBrowser;
  QPushButton *page3CancelButton;
  QPushButton *page3PrevButton;
  QHBoxLayout *page3TopLayout;
  QHBoxLayout *page3MiddleLayout;
  QHBoxLayout *page3BottomLayout;
  QVBoxLayout *page3MainLayout;

  // 总体
  void uiMain(void);
  QListWidget *navigationList;
  QListWidgetItem *item1;
  QListWidgetItem *item2;
  QListWidgetItem *item3;
  QStackedWidget *stack;
  QHBoxLayout *mainLayout;
};

// 定义一个 Convert 类，在 CAJ2PDF 对象中通过异步来转换文件以防止界面卡顿
// Convert 对象的转换结果通过 signals && slots 来和 CAJ2PDF 对象进行交互，以更新
// page3 的界面
class Convert : public QObject {
  Q_OBJECT

 public:
  explicit Convert(QObject *parent = 0) : QObject(parent) {}
  void handleConvert(CAJ2PDF *instance, QString inputFilePath);

 signals:
  void requestUpdateUI(int returnCode, std::string inputFile);
};

#endif  // CAJ2PDF_H
