#pragma once

#include <fstream>
#include <iostream>

#include "datastorage.h"

class FileHandler {
 public:
  FileHandler();
  FileHandler(DataStorage* data);

  ~FileHandler();

  DataStorage* getReadData() const;

  void readFromFile();
  void writeToFile();

 private:
  void setDefaultValues();

  DataStorage* data;
};
