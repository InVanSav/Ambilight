#include "selectingarea.h"

SelectingArea::SelectingArea(QWidget *parent)
    : QGroupBox{parent}, p_isSelecting(false) {}

SelectingArea::SelectingArea(QWidget *parent, DataStorage *data)
    : QGroupBox{parent}, p_isSelecting(false), p_data(data) {
  p_mainLayout = new QVBoxLayout(this);
  setLayout(p_mainLayout);
}

void SelectingArea::saveSelectionToDataStorage(DataStorage *data) {
  // Проверяем, что наша правая точка больше левой
  // Иначе они запишутся наоборот, что будет неправильно
  QPoint start = p_startPos.x() < p_endPos.x() ? p_startPos : p_endPos;
  QPoint end = p_startPos.x() < p_endPos.x() ? p_endPos : p_startPos;

  QRect selectedRect = QRect(start, end);

  QPoint globalTopLeft = mapToGlobal(selectedRect.topLeft());
  QPoint globalBottomRight = mapToGlobal(selectedRect.bottomRight());

  data->setUpperLeftPoint(globalTopLeft.x(), globalTopLeft.y() - p_yTopOffset);
  data->setLowerRightPoint(globalBottomRight.x(),
                           globalBottomRight.y() + p_yBottomOffset);
}

void SelectingArea::paintEvent(QPaintEvent *event) {
  QGroupBox::paintEvent(event);

  QPainter painter(this);

  // Отрисовка белого фона
  painter.fillRect(rect(), Qt::white);

  // Отрисовка прямоугольника
  QRect selectionRect(p_startPos, p_endPos);
  painter.setPen(Qt::black);
  painter.drawRect(selectionRect);
}

void SelectingArea::mousePressEvent(QMouseEvent *event) {
  p_startPos = event->pos();
  p_endPos = p_startPos;
  p_isSelecting = true;
  update();
}

void SelectingArea::mouseMoveEvent(QMouseEvent *event) {
  if (!p_isSelecting) return;

  p_endPos = event->pos();
  correctCoordinates();

  update();
}

void SelectingArea::mouseReleaseEvent(QMouseEvent *event) {
  if (!p_isSelecting) return;

  p_endPos = event->pos();
  p_isSelecting = false;

  correctCoordinates();

  saveSelectionToDataStorage(p_data);

  update();
}

// Не работает, исправить
void SelectingArea::correctCoordinates() {
  QRect fullSelectingAreaRect = rect();

  if (p_endPos.x() > fullSelectingAreaRect.right()) {
    p_endPos.setX(fullSelectingAreaRect.right());
  }

  if (p_endPos.y() > fullSelectingAreaRect.bottom()) {
    p_endPos.setY(fullSelectingAreaRect.bottom());
  }

  if (p_startPos.x() < fullSelectingAreaRect.left()) {
    p_startPos.setX(fullSelectingAreaRect.left());
  }

  if (p_startPos.y() < fullSelectingAreaRect.top()) {
    p_startPos.setY(fullSelectingAreaRect.top());
  }
}
