#include "elevation_dataset.hpp"

#include <fstream>

// CONSTRUCTOR
ElevationDataset::ElevationDataset(const std::string& filename,
                                   size_t width,
                                   size_t height):
    // read in file
    width_{width},
    height_{height},
    data_{ReadData(filename, width, height)},
    max_ele_{GetMax(data_)},
    min_ele_{GetMin(data_)} {};

// GETTER
size_t ElevationDataset::width() const { return width_; }
size_t ElevationDataset::height() const { return height_; };
int ElevationDataset::max_ele() const { return max_ele_; };
int ElevationDataset::min_ele() const { return min_ele_; };
int ElevationDataset::datum_at(size_t row, size_t col) const {
  return data_.at(row).at(col);
};
const std::vector<std::vector<int>>& ElevationDataset::get_data() const {
  return data_;
};

// HELPER
std::vector<std::vector<int>> ElevationDataset::ReadData(
    const std::string& filename, size_t width, size_t height) {
  std::ifstream InputFile(filename);
  std::vector<std::vector<int>> data;
  std::vector<int> dataRow;
  int number;
  int rowCounter = 0;
  int totalCounter = 0;
  while (InputFile >> number) {
    totalCounter += 1;
    if (rowCounter < (int)width) {
      dataRow.push_back(number);
    } else {
      data.push_back(dataRow);
      rowCounter = 0;
      dataRow.clear();
      dataRow.push_back(number);
    }
    rowCounter += 1;
  }
  if (totalCounter != (int)(width * height)) {
    throw std::runtime_error("data dimension mismatch");
  }
  data.push_back(dataRow);
  return data;
}

int ElevationDataset::GetMax(std::vector<std::vector<int>> FileData) {
  int maxHolder = FileData.at(0).at(0);
  for (auto row : FileData) {
    for (auto x : row) {
      if (x > maxHolder) {
        maxHolder = x;
      }
    }
  }
  return maxHolder;
}

int ElevationDataset::GetMin(std::vector<std::vector<int>> FileData) {
  int minHolder = FileData.at(0).at(0);
  for (auto row : FileData) {
    for (auto x : row) {
      if (x < minHolder) {
        minHolder = x;
      }
    }
  }
  return minHolder;
}