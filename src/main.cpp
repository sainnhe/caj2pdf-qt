// -----------------------------------------------------------------------------
// Name:           CAJ2PDF Qt
// Description:    CAJ 转 PDF 转换器
// Author:         Sainnhe Park <i@sainnhe.dev>
// Website:        https://caj2pdf-qt.sainnhe.dev
// License:        GPL3
// -----------------------------------------------------------------------------

#include "caj2pdf.hpp"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  CAJ2PDF w(nullptr, argv[0]);
  w.show();
  return a.exec();
}
