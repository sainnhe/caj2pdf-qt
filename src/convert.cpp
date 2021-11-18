#include "caj2pdf.h"
#include <QDir>

void CAJ2PDF::convert(CAJ2PDF *instance) {
    instance->convertStatus = statusConverting;
    for (QString inputFile : instance->inputFiles) {
        Convert *convertor = new Convert();
        connect(convertor, SIGNAL(requestUpdateUI(int, std::string)), instance, SLOT(updatePage3UI(int, std::string)));
        convertor->handleConvert(instance, inputFile);
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

void Convert::handleConvert(CAJ2PDF *instance, QString inputFileRaw) {
    QTextCodec *codec = QTextCodec::codecForName(instance->codecType.c_str());
    std::string inputFile = codec->fromUnicode(inputFileRaw).data();
    QString currentDirectory = QFileInfo(QString::fromStdString(instance->currentPath)).absolutePath();
    QString caj2pdfExecutablePath = QDir(QDir(currentDirectory).filePath(tr("external"))).filePath(tr("caj2pdf"));
    QString mutoolExecutablePath = QDir(QDir(currentDirectory).filePath(tr("external"))).filePath(tr("mutool"));
    std::string inputFileName = inputFileRaw.toStdString().substr(inputFileRaw.toStdString().find_last_of("/\\") + 1);
    std::string outputFileName = inputFileName.substr(0, inputFileName.find_last_of(".")) + ".pdf";
    QString outputFile = QDir(QString::fromStdString(instance->outputDirectory)).filePath(QString::fromStdString(outputFileName));
    emit requestUpdateUI(system((caj2pdfExecutablePath.toStdString() +
                    " convert \"" + inputFile +
                    "\" -o \"" + codec->fromUnicode(outputFile).data() +
                    "\" -m \"" + mutoolExecutablePath.toStdString() + "\"").c_str()), inputFileRaw.toStdString());
}
