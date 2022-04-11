// -----------------------------------------------------------------------------
// Name:           CAJ2PDF Qt
// Description:    CAJ 转 PDF 转换器
// Author:         Aymeric <343894011@qq.com>
// Website:        https://caj2pdf-qt.sainnhe.dev
// License:        GPL3
// Note:           要想实现无边框效果，需要使用MSVC编译套件，否则MinGW会报错找不到头文件--Aymeric
// -----------------------------------------------------------------------------
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "framelessWindow.h"
//#include <QMainWindow>
#include <QTextCodec>
#include <QButtonGroup>
#include "ui_mainwindow.h"

/*namespace Ui {
class MainWindow;
}*/

// 转换状态
enum ConvertStatus {
    statusNotStarted,   // 尚未开始
    statusConverting,   // 正在转换
    statusFinished      // 转换完成
};

class MainWindow : public CFramelessWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void initialization();
    void initUI();

    std::string outputDirectory;    // 输出目录，默认为第一个输入文件所在的目录
    QString currentDir;             // 编译出来的可执行文件所在的目录，用来定位 /external/caj2pdf 和 /external/mutool
    ConvertStatus convertStatus;    // 转换状态，用来设置按钮的行为
    std::string codecType;          // 编码类型，用来解决 windows 下的中文路径问题

protected:
    void closeEvent(QCloseEvent* event) override;    // 重写closeEvent的申明
    void dragEnterEvent(QDragEnterEvent* event) override;//拖进事件
    void dropEvent(QDropEvent* event) override;//放下事件

private slots:
    /**
     * @brief 最小化窗口
     */
    void slot_miniWindow();
    /**
     * @brief 最大化窗口
     */
    void slot_maxWindow();
    /**
     * @brief 关闭窗口
     */
    void slot_closeWindow();

    // 总体
    /**
     * @brief slot_cancle
     */
    void slot_cancle();
    /**
     * @brief 处理页码变化时 ui 要做的更新
     * @param index 要变化的页码
     */
    void slot_curIndexChanged(int index);
    /**
     * @brief 返回上一页
     */
    void slot_preButton();

    void slot_openWhatIsThis();

    // 第一步
    /**
     * @brief 处理第一页的选择输入文件按钮和第二页的选择输出目录按钮的槽
     * 1、打开一个文件选择窗口，选择一个或多个 CAJ 文件，将结果放入 inputFiles ；
     * 将这些文件的绝对路径写入 inputTextBrowser 和 outputTextBrowser 。
     * 2、打开一个目录选择窗口来选择目录，将结果放入 outputDirectory
     */
    void slot_selectInputOutput();
    /**
     * @brief 处理每一页的下一步按钮以及最后的完成按钮的槽
     * 1、如果未选择任何文件，则弹出一个警告框并返回；
     * 否则更新 stack 和 navigationList, 切换到下一页；
     * 将第一个输入文件所在目录设置为默认输出目录。
     * 2、如果转换正在进行中或者已结束，则只更新 stack 和 navigationList 来切换页面；
     * 否则先检测输出目录是否存在，若不存在则弹出一个警告框并返回；
     * 若存在则更新 outputDirectory 和 progressBar ，然后开始异步转换。
     * 3、这个（完成）按钮只有当转换完成后才会被启用；
     * 点击后返回输入文件界面
     */
    void slot_nextAndFinish();

    // 第三步
    /**
     * @brief 当处理完成后会调用此函数，更新处理结果
     * @param returnCode    处理结果代码
     * @param inputFile     处理的文件
     */
    void slot_showConvertResult(int returnCode, std::string inputFile);


signals:
    void signal_curIndexChanged(int index);

private:
    Ui::MainWindow* ui;
    static void convert(MainWindow* instance);
    //void handleWhatsThisEntry();    // windows 下的 ？按钮所调用的函数

    QList<QString> inputFiles;
    QButtonGroup* btnGrp;
    // 总体
    int curIndex;

    std::string version;
};

// 定义一个 Convert 类，在 CAJ2PDF 对象中通过异步来转换文件以防止界面卡顿
// Convert 对象的转换结果通过 signals && slots 来和 CAJ2PDF 对象进行交互，以更新 page3 的界面
class Convert : public QObject {
    Q_OBJECT

public:
    explicit Convert(QObject* parent = 0) : QObject(parent) {}
    void handleConvert(MainWindow* instance, QString inputFileRaw);

signals:
    void requestUpdateUI(int returnCode, std::string inputFile);
};

#endif // MAINWINDOW_H
