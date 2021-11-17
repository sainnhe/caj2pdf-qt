#include "caj2pdf.h"
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>

void CAJ2PDF::handlePage2SelectOutputButton() {
    outputDirectory = QFileDialog::getExistingDirectory(this,
            tr("选择目录"),
            QDir::homePath(),
            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    selectOutputLineEdit->setText(outputDirectory);
}

void CAJ2PDF::handlePage2CancelButton() {
    QApplication::quit();
}

void CAJ2PDF::handlePage2PrevButton() {
    stack->setCurrentIndex(0);
    navigationList->setCurrentRow(0);
}

void CAJ2PDF::handlePage2NextButton() {
    if (!std::filesystem::is_directory(selectOutputLineEdit->text().toStdString())) {
        QMessageBox::warning(this, tr("警告"), tr("请选择一个存在的目录"));
        return;
    }
    outputDirectory = selectOutputLineEdit->text();
    stack->setCurrentIndex(2);
    navigationList->setCurrentRow(2);
    navigationList->item(2)->setFlags(
            navigationList->item(2)->flags().setFlag(Qt::ItemIsEnabled, true));
}
