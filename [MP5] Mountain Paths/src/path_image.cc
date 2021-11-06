#include "path_image.hpp"

#include <cmath>
#include <fstream>

// CONSTRUCTOR
PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset) {
  // r is the row number here
  for (int r = 0; r < (int)dataset.height(); r++) {
    // keeps track of the row of a best move
    int rowHolder = r;
    // initialize path p for the specific starting row
    Path p = {dataset.width(), (size_t)r};
    // move to next columns
    for (int c = 0; c < (int)dataset.width() - 1; c++) {
      if (c == 0) {
        p.set_loc((size_t)c, (size_t)r);
      }
      int currentDatum = dataset.datum_at((size_t)rowHolder, (size_t)c);
      // nextMoves contains all three possible moves, whith each move being a
      // pair of integers nextMoves.at(0).first gives the actual elevation,
      // nextMoves.at(0).second gives the corresponding row number
      std::vector<std::pair<int, int>> nextMoves;
      // first row
      if (rowHolder == 0) {
        nextMoves.push_back(std::make_pair(
            abs(currentDatum -
                dataset.datum_at((size_t)rowHolder, (size_t)c + 1)),
            rowHolder));
        nextMoves.push_back(std::make_pair(
            abs(currentDatum -
                dataset.datum_at((size_t)rowHolder + 1, (size_t)c + 1)),
            rowHolder + 1));
        // returns the best choice for next move
        std::pair<int, int> bestNextMove = getNextMoveFirstRow(nextMoves);
        p.set_loc(c + 1, (size_t)bestNextMove.second);
        p.inc_ele_change(bestNextMove.first);
        rowHolder = bestNextMove.second;
      }
      // last row
      else if (rowHolder == (int)dataset.height() - 1) {
        nextMoves.push_back(std::make_pair(
            abs(currentDatum -
                dataset.datum_at((size_t)rowHolder - 1, (size_t)c + 1)),
            rowHolder - 1));
        nextMoves.push_back(std::make_pair(
            abs(currentDatum -
                dataset.datum_at((size_t)rowHolder, (size_t)c + 1)),
            rowHolder));
        // returns the best choice for next move
        std::pair<int, int> bestNextMove = getNextMoveLastRow(nextMoves);
        p.set_loc(c + 1, (size_t)bestNextMove.second);
        p.inc_ele_change(bestNextMove.first);
        rowHolder = bestNextMove.second;

      }
      // normal rows
      else {
        nextMoves.push_back(std::make_pair(
            abs(currentDatum -
                dataset.datum_at((size_t)rowHolder - 1, (size_t)c + 1)),
            rowHolder - 1));
        nextMoves.push_back(std::make_pair(
            abs(currentDatum -
                dataset.datum_at((size_t)rowHolder, (size_t)c + 1)),
            rowHolder));
        nextMoves.push_back(std::make_pair(
            abs(currentDatum -
                dataset.datum_at((size_t)rowHolder + 1, (size_t)c + 1)),
            rowHolder + 1));
        // returns the best choice for next move
        std::pair<int, int> bestNextMove = getNextMove(nextMoves);
        p.set_loc(c + 1, (size_t)bestNextMove.second);
        p.inc_ele_change(bestNextMove.first);
        rowHolder = bestNextMove.second;
      }
    }
    paths_.push_back(p);
  }
  // path image processing
  path_image_ = image.get_image();
  int minElevPath = MinElev();
  Color red = {252, 25, 63};
  Color green = {31, 253, 13};
  for (int r = 0; r < (int)paths_.size(); r++) {
    Path p = paths_.at(r);
    for (int c = 0; c < (int)p.length(); c++) {
      path_image_.at(p.path().at(c)).at(c) = red;
    }
  }
  for (int r = 0; r < (int)paths_.size(); r++) {
    Path p = paths_.at(r);
    for (int c = 0; c < (int)p.length(); c++) {
      if (minElevPath == r) {
        path_image_.at(p.path().at(c)).at(c) = green;
      }
    }
  }
  width_ = dataset.width();
  height_ = dataset.height();
}

// GETTERS
size_t PathImage::width() const { return width_; }
size_t PathImage::height() const { return height_; }
unsigned int PathImage::max_color_value() const { return max_color_value_; }
const std::vector<Path>& PathImage::paths() const { return paths_; }
const std::vector<std::vector<Color>>& PathImage::path_image() const {
  return path_image_;
}

// PPM
void PathImage::to_ppm(const std::string& name) const {
  std::ofstream output(name);
  // std::ofstream output(name + ".ppm", std::ofstream::out);
  output << "P3" << std::endl;
  output << width_ << " " << height_ << std::endl;
  output << "255" << std::endl;
  for (auto row : path_image_) {
    for (auto x : row) {
      output << x.red() << " " << x.green() << " " << x.blue() << " ";
    }
    output << "\n";
  }
  output << "\n";
  // output.close();
}

// HELPERS
std::pair<int, int> PathImage::getNextMove(
    std::vector<std::pair<int, int>> nextMoves) {
  // Tie with Straight
  if (nextMoves.at(1).first == nextMoves.at(0).first &&
      nextMoves.at(1).first < nextMoves.at(2).first) {
    return nextMoves.at(1);
  }
  if (nextMoves.at(1).first == nextMoves.at(2).first &&
      nextMoves.at(1).first < nextMoves.at(0).first) {
    return nextMoves.at(1);
  }
  // Three-way tie
  if (nextMoves.at(1).first == nextMoves.at(2).first &&
      nextMoves.at(1).first == nextMoves.at(0).first) {
    return nextMoves.at(1);
  }
  // Non-Straight Ties
  if (nextMoves.at(0).first == nextMoves.at(2).first &&
      nextMoves.at(0).first < nextMoves.at(1).first) {
    return nextMoves.at(2);
  }
  // No Tie
  if (nextMoves.at(1).first < nextMoves.at(2).first &&
      nextMoves.at(1).first < nextMoves.at(0).first) {
    return nextMoves.at(1);
  }
  if (nextMoves.at(0).first < nextMoves.at(1).first &&
      nextMoves.at(0).first < nextMoves.at(2).first) {
    return nextMoves.at(0);
  }
  if (nextMoves.at(2).first < nextMoves.at(1).first &&
      nextMoves.at(2).first < nextMoves.at(0).first) {
    return nextMoves.at(2);
  }
  // No Tie Situation
  // int minValHolder = nextMoves.at(0).first;
  // std::pair<int, int> minHolder = nextMoves.at(0);
  // for (auto x : nextMoves) {
  //   if (x.first < minValHolder) {
  //     minValHolder = x.first;
  //     minHolder = x;
  //   }
  // }
  // return minHolder;
  // std::cout << nextMoves.at(0).first << std::endl;
  // std::cout << nextMoves.at(1).first << std::endl;
  // std::cout << nextMoves.at(2).first << std::endl;
  return nextMoves.at(3);
}

std::pair<int, int> PathImage::getNextMoveFirstRow(
    std::vector<std::pair<int, int>> nextMoves) {
  // Tie
  if (nextMoves.at(0).first == nextMoves.at(1).first) {
    return nextMoves.at(0);
  }
  // No Tie
  else {
    if (nextMoves.at(0).first < nextMoves.at(1).first) {
      return nextMoves.at(0);
    } else {
      return nextMoves.at(1);
    }
  }
}

std::pair<int, int> PathImage::getNextMoveLastRow(
    std::vector<std::pair<int, int>> nextMoves) {
  // Tie
  if (nextMoves.at(0).first == nextMoves.at(1).first) {
    return nextMoves.at(1);
  }
  // No Tie
  else {
    if (nextMoves.at(0).first < nextMoves.at(1).first) {
      return nextMoves.at(0);
    } else {
      return nextMoves.at(1);
    }
  }
}

int PathImage::MinElev() {
  int minholder = paths_.at(0).ele_change();
  int toReturn = 0;
  for (int i = 0; i < (int)paths_.size(); i++) {
    if ((int)paths_.at(i).ele_change() < minholder) {
      minholder = (int)paths_.at(i).ele_change();
      toReturn = i;
    }
  }
  std::cout << "minimum elevation: " << minholder << std::endl;
  std::cout << "number: " << toReturn << std::endl;
  return toReturn;
}