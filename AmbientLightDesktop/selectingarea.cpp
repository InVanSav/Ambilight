#include "selectingarea.h"

SelectingArea::SelectingArea(QWidget *parent)
    : QWidget{parent}, p_isSelecting(false) {}

SelectingArea::SelectingArea(QWidget *parent, DataStorage *data)
    : QWidget{parent}, p_isSelecting(false), p_data(data) {
  p_mainLayout = new QVBoxLayout(this);
  setLayout(p_mainLayout);

  p_primaryScreen = QGuiApplication::primaryScreen()->geometry();

  setFixedHeight(p_primaryScreen.height() - p_yOffset);
  setFixedWidth(p_primaryScreen.width() - p_xOffset);

  // Рассчитываем отношение размеров SelectingArea к размерам экрана
  p_widthRatio =
      static_cast<qreal>(p_primaryScreen.width()) / static_cast<qreal>(width());
  p_heightRatio = static_cast<qreal>(p_primaryScreen.height()) /
                  static_cast<qreal>(height());

  auto upperLeftPair = p_data->getUpperLeftPoint();
  auto lowerRightPair = p_data->getLowerRightPoint();

  QPoint upperLeft(upperLeftPair.first / p_widthRatio,
                   upperLeftPair.second / p_heightRatio);
  QPoint lowerRight(
      lowerRightPair.first / p_widthRatio + upperLeftPair.first,
      lowerRightPair.second / p_heightRatio + upperLeftPair.second);

  p_startPos = upperLeft;
  p_endPos = lowerRight;
}

void SelectingArea::saveSelectionToDataStorage(DataStorage *data) {
  // Проверяем, что наша правая точка больше левой
  QPoint start = p_startPos.x() < p_endPos.x() ? p_startPos : p_endPos;
  QPoint end = p_startPos.x() < p_endPos.x() ? p_endPos : p_startPos;

  // Пересчитываем координаты в координаты экрана
  QRect selectedRect(
      QPoint(start.x() * p_widthRatio, start.y() * p_heightRatio),
      QPoint(end.x() * p_widthRatio - start.x(),
             end.y() * p_heightRatio - start.y()));

  QPoint globalTopLeft = selectedRect.topLeft();
  QPoint globalBottomRight = selectedRect.bottomRight();

  data->setUpperLeftPoint(globalTopLeft.x(), globalTopLeft.y());
  data->setLowerRightPoint(globalBottomRight.x(), globalBottomRight.y());
}

void SelectingArea::paintEvent(QPaintEvent *event) {
  QWidget::paintEvent(event);

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
  //  if (p_endPos.x() > p_fullSelectingArea.right()) {
  //    p_endPos.setX(p_fullSelectingArea.right());
  //  }

  //  if (p_endPos.y() > p_fullSelectingArea.bottom()) {
  //    p_endPos.setY(p_fullSelectingArea.bottom());
  //  }

  //  if (p_startPos.x() < p_fullSelectingArea.left()) {
  //    p_startPos.setX(p_fullSelectingArea.left());
  //  }

  //  if (p_startPos.y() < p_fullSelectingArea.top()) {
  //    p_startPos.setY(p_fullSelectingArea.top());
  //  }
}
