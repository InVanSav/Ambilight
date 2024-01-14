#include "datastorage.h"

DataStorage::DataStorage(const std::string& ip, const std::string& port,
                         const std::vector<std::string>& colors,
                         int upperLeftPointX, int upperLeftPointY,
                         int lowerRightPointX, int lowerRightPointY)
    : ip(ip),
      port(port),
      colors(colors),
      upperLeftPointX(upperLeftPointX),
      upperLeftPointY(upperLeftPointY),
      lowerRightPointX(lowerRightPointX),
      lowerRightPointY(lowerRightPointY) {}

const std::string& DataStorage::getIp() const { return ip; }

void DataStorage::setIp(const std::string& newIp) { ip = newIp; }

const std::string& DataStorage::getPort() const { return port; }

void DataStorage::setPort(const std::string& newPort) { port = newPort; }

const std::vector<std::string>& DataStorage::getColors() const {
  return colors;
}

void DataStorage::setColors(const std::vector<std::string>& newColors) {
  colors = newColors;
}

std::pair<int, int> DataStorage::getUpperLeftPoint() const {
  return std::make_pair(upperLeftPointX, upperLeftPointY);
}

void DataStorage::setUpperLeftPoint(int x, int y) {
  upperLeftPointX = x;
  upperLeftPointY = y;
}

std::pair<int, int> DataStorage::getLowerRightPoint() const {
  return std::make_pair(lowerRightPointX, lowerRightPointY);
}

void DataStorage::setLowerRightPoint(int x, int y) {
  lowerRightPointX = x;
  lowerRightPointY = y;
}
