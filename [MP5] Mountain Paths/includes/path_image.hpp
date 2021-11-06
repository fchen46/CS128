#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cstdlib>  // for size_t
#include <vector>

#include "color.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"

class PathImage {
public:
  // CONSTRUCTOR
  PathImage(const GrayscaleImage& image, const ElevationDataset& dataset);
  // GETTER
  size_t width() const;
  size_t height() const;
  unsigned int max_color_value() const;
  const std::vector<Path>& paths() const;
  const std::vector<std::vector<Color>>& path_image() const;
  void to_ppm(const std::string& name) const;
  // HELPER
  std::pair<int, int> getNextMove(std::vector<std::pair<int, int>> nextMoves);
  std::pair<int, int> getNextMoveFirstRow(
      std::vector<std::pair<int, int>> nextMoves);
  std::pair<int, int> getNextMoveLastRow(
      std::vector<std::pair<int, int>> nextMoves);
  int MinElev();

private:
  std::vector<Path> paths_;
  size_t width_;
  size_t height_;
  std::vector<std::vector<Color>> path_image_;
  static const int max_color_value_ = 255;
};

#endif