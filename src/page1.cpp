#include "caj2pdf.h"
#include <QFileDialog>
#include <string>

void CAJ2PDF::handlePage1SelectInputButton() {
    inputFiles = QFileDialog::getOpenFileNames(this,
            tr("打开 CAJ 文件"), QDir::homePath(), tr("CAJ 文件 (*.caj)"));
    QString inputFilesText = tr("");
    for (QString str : inputFiles) {
        inputFilesText = inputFilesText + str + "\n";
    }
    inputTextBrowser->setText(inputFilesText);
    outputTextBrowser->setText(inputFilesText);
    std::string defaultDir = std::filesystem::path(inputFiles[0].toStdString()).parent_path().u8string();
    selectOutputLineEdit->setText(QString::fromStdString(defaultDir));
}

void CAJ2PDF::handlePage1NextButton() {
    if (inputFiles.empty()) {
        QMessageBox::warning(this, tr("警告"), tr("未选择 CAJ 文件"));
        return;
    }
    stack->setCurrentIndex(1);
    navigationList->setCurrentRow(1);
    navigationList->item(1)->setFlags(
            navigationList->item(1)->flags().setFlag(Qt::ItemIsEnabled, true));
}
