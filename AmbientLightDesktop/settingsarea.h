#pragma once

#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QRegularExpression>

#include "datastorage.h"

class SettingsArea : public QGroupBox {
  Q_OBJECT
 public:
  explicit SettingsArea(QWidget *parent, DataStorage *data);

 private slots:
  void validateIp(const QString &text);
  void validatePort(const QString &text);

 private:
  QLineEdit *p_ipLineEdit;
  QLineEdit *p_portLineEdit;

  DataStorage *p_data;
};
