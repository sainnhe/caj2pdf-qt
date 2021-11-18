#include "caj2pdf.h"
#include <QFileDialog>

void CAJ2PDF::handlePage2SelectOutputButton() {
    outputDirectory = QFileDialog::getExistingDirectory(this,
            tr("选择目录"),
            QDir::homePath(),
            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks).toStdString();
    selectOutputLineEdit->setText(QString::fromStdString(outputDirectory));
}

void CAJ2PDF::handlePage2PrevButton() {
    stack->setCurrentIndex(0);
    navigationList->setCurrentRow(0);
}

void CAJ2PDF::handlePage2NextButton() {
    if (convertStatus == statusNotStarted) {
        if (!QDir(selectOutputLineEdit->text()).exists()) {
            QMessageBox::warning(this, tr("警告"), tr("请选择一个存在的目录"));
            return;
        }
        outputDirectory = selectOutputLineEdit->text().toStdString();
        progressBar->setRange(0, inputFiles.capacity());
        progressBar->setValue(0);
        QFuture<void> future = QtConcurrent::run(convert, this);
    }
    stack->setCurrentIndex(2);
    navigationList->setCurrentRow(2);
    navigationList->item(2)->setFlags(
            navigationList->item(2)->flags().setFlag(Qt::ItemIsEnabled, true));
}
