#include "caj2pdf.h"
#include <QDir>

void CAJ2PDF::convert(CAJ2PDF *instance) {
    instance->convertStatus = statusConverting;
    QTextCodec *codec = QTextCodec::codecForName(instance->codecType.c_str());
    for (QString inputFile : instance->inputFiles) {
        Convert *convertor = new Convert();
        connect(convertor, SIGNAL(requestUpdateUI(int, std::string)), instance, SLOT(updatePage3UI(int, std::string)));
        convertor->handleConvert(instance, codec->fromUnicode(inputFile).data());
    }
    instance->convertStatus = statusFinished;
    instance->page3NextButton->setDisabled(false);
}

void CAJ2PDF::updatePage3UI(int returnCode, std::string inputFile) {
    progressBar->setValue(progressBar->value() + 1);
    if (returnCode == 0) {
        statusTextBrowser->insertPlainText(QString::fromStdString("✅ " + inputFile + "\n"));
    } else {
        statusTextBrowser->insertPlainText(QString::fromStdString("❌ " + inputFile + "\n"));
    }
}

void Convert::handleConvert(CAJ2PDF *instance, std::string inputFile) {
    QString currentDirectory = QFileInfo(QString::fromStdString(instance->currentPath)).absolutePath();
    QString caj2pdfExecutablePath = QDir(QDir(currentDirectory).filePath(tr("external"))).filePath(tr("caj2pdf"));
    QString mutoolExecutablePath = QDir(QDir(currentDirectory).filePath(tr("external"))).filePath(tr("mutool"));
    std::string inputFileName = inputFile.substr(inputFile.find_last_of("/\\") + 1);
    std::string outputFileName = inputFileName.substr(0, inputFileName.find_last_of(".")) + ".pdf";
    QString outputFile = QDir(QString::fromStdString(instance->outputDirectory)).filePath(QString::fromStdString(outputFileName));
    emit requestUpdateUI(system((caj2pdfExecutablePath.toStdString() +
                    " convert \"" + inputFile +
                    "\" -o \"" + outputFile.toStdString() +
                    "\" -m \"" + mutoolExecutablePath.toStdString() + "\"").c_str()), inputFile);
}
