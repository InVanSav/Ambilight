#pragma once

#include <QApplication>
#include <QGroupBox>
#include <QMouseEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <QWidget>

#include "datastorage.h"

class SelectingArea : public QWidget {
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

  QRect p_primaryScreen;

  qreal p_widthRatio;
  qreal p_heightRatio;

  int p_yOffset = 300;
  int p_xOffset = 30;
};
