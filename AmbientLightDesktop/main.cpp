#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QApplication::setApplicationName("AmbilightDesktop");

  MainWindow w;
  w.show();
  w.showMaximized();

  return a.exec();
}
