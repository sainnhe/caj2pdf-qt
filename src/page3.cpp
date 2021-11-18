#include "caj2pdf.h"

void CAJ2PDF::handlePage3PrevButton() {
    stack->setCurrentIndex(1);
    navigationList->setCurrentRow(1);
}

void CAJ2PDF::handlePage3NextButton() {
    QApplication::quit();
}
