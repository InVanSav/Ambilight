#pragma once

#include <selectingarea.h>
#include <settingsarea.h>

#include <QMainWindow>
#include <QPushButton>

#include "filehandler.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
};
