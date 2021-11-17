#include "caj2pdf.h"
#include <QDir>
#include <filesystem>

void CAJ2PDF::convert(CAJ2PDF *instance) {
    for (QString inputFile : instance->inputFiles) {
        handleConvert(instance, inputFile.toStdString());
    }
}

void CAJ2PDF::handleConvert(CAJ2PDF *instance, std::string inputFile) {
    QString currentDirectory = QFileInfo(QString::fromStdString(instance->currentPath)).absolutePath();
    QString caj2pdfExecutablePath = QDir(QDir(currentDirectory).filePath(tr("external"))).filePath(tr("caj2pdf"));
    std::string inputFileName = std::filesystem::path(inputFile).filename();
    std::string outputFileName = inputFileName.substr(0, inputFileName.find_last_of(".")) + ".pdf";
    QString outputFile = QDir(QString::fromStdString(instance->outputDirectory.toStdString())).filePath(QString::fromStdString(outputFileName));
    int returnCode = system((caj2pdfExecutablePath.toStdString() + " convert \"" + inputFile + "\" -o \"" + outputFile.toStdString() + "\"").c_str());
}
