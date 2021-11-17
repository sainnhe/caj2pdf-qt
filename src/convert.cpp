#include "caj2pdf.h"
#include <QDir>
#include <filesystem>

bool CAJ2PDF::convert(std::string inputFile, std::string outputDirectory) {
    QString currentDirectory = QFileInfo(QString::fromStdString(currentPath)).absolutePath();
    QString caj2pdfExecutablePath = QDir(QDir(currentDirectory).filePath(tr("external"))).filePath(tr("caj2pdf"));
    std::string inputFileName = std::filesystem::path(inputFile).filename();
    std::string outputFileName = inputFileName.substr(0, inputFileName.find_last_of(".")) + ".pdf";
    QString outputFile = QDir(QString::fromStdString(outputDirectory)).filePath(QString::fromStdString(outputFileName));
    system((caj2pdfExecutablePath.toStdString() + " convert " + inputFile + " -o " + outputFile.toStdString()).c_str());
    return true;
}
