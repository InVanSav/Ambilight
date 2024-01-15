#include "settingsarea.h"

SettingsArea::SettingsArea(QWidget *parent, DataStorage *data)
    : QGroupBox{parent}, p_data(data) {
  setTitle("Settings");

  QGridLayout *layout = new QGridLayout(this);

  QLabel *ipLabel = new QLabel("IP:", this);
  p_ipLineEdit =
      new QLineEdit(data ? QString::fromStdString(data->getIp()) : "", this);
  connect(p_ipLineEdit, &QLineEdit::textChanged, this,
          &SettingsArea::validateIp);

  QLabel *portLabel = new QLabel("Port:", this);
  p_portLineEdit =
      new QLineEdit(data ? QString::fromStdString(data->getPort()) : "", this);
  connect(p_portLineEdit, &QLineEdit::textChanged, this,
          &SettingsArea::validatePort);

  layout->addWidget(ipLabel, 0, 0);
  layout->addWidget(p_ipLineEdit, 0, 1);

  layout->addWidget(portLabel, 1, 0);
  layout->addWidget(p_portLineEdit, 1, 1);
}

void SettingsArea::validateIp(const QString &text) {
  QRegularExpression ipRegex("^\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}$");
  QRegularExpressionMatch match = ipRegex.match(text);

  if (!match.hasMatch()) {
    p_ipLineEdit->setStyleSheet("color: red;");
    return;
  }

  p_ipLineEdit->setStyleSheet("");
  p_data->setIp(text.toStdString());
}

void SettingsArea::validatePort(const QString &text) {
  bool ok;
  int port = text.toInt(&ok);

  if (!ok || port <= 0 || port >= 65535) {
    p_portLineEdit->setStyleSheet("color: red;");
    return;
  }

  p_portLineEdit->setStyleSheet("");
  p_data->setPort(text.toStdString());
}
