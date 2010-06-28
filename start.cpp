#include "common.h"

#include <QtGui/QApplication>

int main(int argc, char *argv[]) {
  /* initialize random seed: */
  srand ( time(NULL) );
  QApplication app(argc, argv);
  window mainWindow;
  mainWindow.show();

  return app.exec();
}


