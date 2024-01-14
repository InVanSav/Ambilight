#include "filehandler.h"

FileHandler::FileHandler() : data(nullptr) { readFromFile(); }

FileHandler::FileHandler(DataStorage* data) : data(data) {}

DataStorage* FileHandler::getReadData() const { return data; }

void FileHandler::readFromFile() {
  std::ifstream file("settings.cfg");

  if (!file.good()) {
    setDefaultValues();
    writeToFile();
    return;
  }

  std::string line;
  std::string ip;
  std::string port;
  std::vector<std::string> colors;
  int upperLeftPointX = 0;
  int upperLeftPointY = 0;
  int lowerRightPointX = 0;
  int lowerRightPointY = 0;

  while (std::getline(file, line)) {
    size_t pos = line.find('=');
    if (pos != std::string::npos) {
      std::string key = line.substr(0, pos);
      std::string value = line.substr(pos + 1);

      if (key == "ip") {
        ip = value;
      } else if (key == "port") {
        port = value;
      } else if (key == "colors") {
        // Разделение строки с цветами на массив
        size_t commaPos;
        while ((commaPos = value.find(',')) != std::string::npos) {
          colors.push_back(value.substr(0, commaPos));
          value.erase(0, commaPos + 1);
        }
        colors.push_back(value);
      } else if (key == "upper_left_point_x") {
        upperLeftPointX = std::stoi(value);
      } else if (key == "upper_left_point_y") {
        upperLeftPointY = std::stoi(value);
      } else if (key == "lower_right_point_x") {
        lowerRightPointX = std::stoi(value);
      } else if (key == "lower_right_point_y") {
        lowerRightPointY = std::stoi(value);
      }
    }
  }

  file.close();

  // Освобождаем память, если указатель уже был инициализирован
  delete data;

  data = new DataStorage(ip, port, colors, upperLeftPointX, upperLeftPointY,
                         lowerRightPointX, lowerRightPointY);
}

void FileHandler::writeToFile() {
  std::ofstream file("settings.cfg");

  if (!file.is_open()) {
    std::cerr << "Не удалось открыть файл для записи" << std::endl;
    return;
  }

  // Получение считанных данных из DataStorage
  const DataStorage* readData = getReadData();

  // Запись данных в файл
  file << "ip=" << readData->getIp() << std::endl;
  file << "port=" << readData->getPort() << std::endl;

  file << "colors=";
  if (!readData->getColors().empty())
    for (const auto& color : readData->getColors()) {
      file << color << ",";
    }
  file << std::endl;

  // Получение и запись координат
  auto upperLeftPoint = readData->getUpperLeftPoint();
  file << "upper_left_point_x=" << upperLeftPoint.first << std::endl;
  file << "upper_left_point_y=" << upperLeftPoint.second << std::endl;

  auto lowerRightPoint = readData->getLowerRightPoint();
  file << "lower_right_point_x=" << lowerRightPoint.first << std::endl;
  file << "lower_right_point_y=" << lowerRightPoint.second << std::endl;

  file.close();
}

void FileHandler::setDefaultValues() {
  data = new DataStorage("", "", {}, 0, 0, 0, 0);
}

FileHandler::~FileHandler() { delete data; }
