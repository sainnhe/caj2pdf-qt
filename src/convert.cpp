#include "caj2pdf.h"
#include <QDir>
#ifdef _WIN32
#include <windows.h>
#endif

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
    QString caj2pdfExecutablePathRaw = QDir(QDir(currentDirectory).filePath(tr("external"))).filePath(tr("caj2pdf"));
    std::string caj2pdfExecutablePath = codec->fromUnicode(caj2pdfExecutablePathRaw).data();
    QString mutoolExecutablePathRaw = QDir(QDir(currentDirectory).filePath(tr("external"))).filePath(tr("mutool"));
    std::string mutoolExecutablePath = codec->fromUnicode(mutoolExecutablePathRaw).data();
    std::string inputFileName = inputFileRaw.toStdString().substr(inputFileRaw.toStdString().find_last_of("/\\") + 1);
    std::string outputFileName = inputFileName.substr(0, inputFileName.find_last_of(".")) + ".pdf";
    QString outputFileRaw = QDir(QString::fromStdString(instance->outputDirectory)).filePath(QString::fromStdString(outputFileName));
    std::string outputFile = codec->fromUnicode(outputFileRaw).data();
    if (!QString::compare(QSysInfo::kernelType(), tr("winnt"))) {
        emit requestUpdateUI(WinExec((caj2pdfExecutablePath +
                        " convert \"" + inputFile +
                        "\" -o \"" + outputFile +
                        "\" -m \"" + mutoolExecutablePath + "\"").c_str(), SW_HIDE) <= 31, inputFileRaw.toStdString());
    } else {
        emit requestUpdateUI(system((caj2pdfExecutablePath +
                        " convert \"" + inputFile +
                        "\" -o \"" + outputFile +
                        "\" -m \"" + mutoolExecutablePath + "\"").c_str()), inputFileRaw.toStdString());
    }
}
