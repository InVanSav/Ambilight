#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  FileHandler *fileHandler = new FileHandler;
  DataStorage *readData = fileHandler->getReadData();

  QRect screen = QGuiApplication::primaryScreen()->geometry();

  setFixedSize(screen.width(), screen.height());
  setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

  SettingsArea *settingsArea = new SettingsArea(this, readData);
  settingsArea->setFixedHeight(100);
  SelectingArea *selectingArea = new SelectingArea(this, readData);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(settingsArea);
  mainLayout->addWidget(selectingArea);

  QWidget *centralWidget = new QWidget(this);
  centralWidget->setLayout(mainLayout);
  setCentralWidget(centralWidget);

  QPushButton *confirmButton = new QPushButton("Confirm", this);
  connect(confirmButton, &QPushButton::clicked,
          [=]() { fileHandler->writeToFile(); });

  mainLayout->addWidget(confirmButton, Qt::AlignBottom | Qt::AlignRight);
}

MainWindow::~MainWindow() {}
