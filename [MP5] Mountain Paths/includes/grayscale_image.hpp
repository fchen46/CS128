#ifndef GRAYSCALE_IMAGE_H
#define GRAYSCALE_IMAGE_H

#include <cstdlib>  // for size_t
#include <vector>

#include "color.hpp"
#include "elevation_dataset.hpp"

class GrayscaleImage {
public:
  // CONSTRUCTOR
  GrayscaleImage(const ElevationDataset& dataset);
  GrayscaleImage(const std::string& filename, size_t width, size_t height);
  // GETTER
  size_t width() const { return width_; }
  size_t height() const { return height_; }
  unsigned int max_color_value() const { return max_color_value_; }
  const Color& color_at(int row, int col) const { return image_[row][col]; }
  const std::vector<std::vector<Color>>& get_image() const { return image_; }
  void to_ppm(const std::string& name) const;

private:
  size_t width_;
  size_t height_;
  std::vector<std::vector<Color>> image_;
  static const int max_color_value_ = 255;
};

#endif