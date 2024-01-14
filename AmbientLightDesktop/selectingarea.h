#pragma once

#include <QGroupBox>
#include <QMouseEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <QWidget>

#include "datastorage.h"

class SelectingArea : public QGroupBox {
  Q_OBJECT
 public:
  explicit SelectingArea(QWidget *parent = nullptr);
  explicit SelectingArea(QWidget *parent = nullptr,
                         DataStorage *data = nullptr);

 protected:
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

 private:
  void saveSelectionToDataStorage(DataStorage *data);
  void correctCoordinates();

 private:
  QVBoxLayout *p_mainLayout;

  DataStorage *p_data;

  QPoint p_startPos;
  QPoint p_endPos;
  QRect *p_selectionRect;

  bool p_isSelecting;

  int p_yTopOffset = 130;
  int p_yBottomOffset = 30;
};
