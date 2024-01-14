#pragma once

#include <string>
#include <vector>

class DataStorage {
 public:
  DataStorage(const std::string& ip, const std::string& port,
              const std::vector<std::string>& colors, int upperLeftPointX,
              int upperLeftPointY, int lowerRightPointX, int lowerRightPointY);

  const std::string& getIp() const;
  void setIp(const std::string& newIp);

  const std::string& getPort() const;
  void setPort(const std::string& newPort);

  const std::vector<std::string>& getColors() const;
  void setColors(const std::vector<std::string>& newColors);

  std::pair<int, int> getUpperLeftPoint() const;
  void setUpperLeftPoint(int x, int y);

  std::pair<int, int> getLowerRightPoint() const;
  void setLowerRightPoint(int x, int y);

 private:
  std::string ip;
  std::string port;
  std::vector<std::string> colors;
  int upperLeftPointX;
  int upperLeftPointY;
  int lowerRightPointX;
  int lowerRightPointY;
};
