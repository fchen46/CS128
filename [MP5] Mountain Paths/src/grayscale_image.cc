#include "grayscale_image.hpp"

#include <cmath>
#include <fstream>

// CONSTRUCTOR
GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  if (dataset.max_ele() == dataset.min_ele()) {
    for (int i = 0; i < (int)dataset.height(); i++) {
      std::vector<Color> holder;
      for (int j = 0; j < (int)dataset.width(); j++) {
        int shade_of_gray = 0;
        Color c = {shade_of_gray, shade_of_gray, shade_of_gray};
        holder.push_back(c);
      }
      image_.push_back(holder);
    }
  } else {
    for (auto row : dataset.get_data()) {
      std::vector<Color> holder;
      for (auto x : row) {
        double shade =
            255.0 * ((double)(x - dataset.min_ele()) /
                     (double)(dataset.max_ele() - dataset.min_ele()));
        int shade_of_gray = std::round(shade);
        // std::cout << shade_of_gray << std::endl;
        Color c = {shade_of_gray, shade_of_gray, shade_of_gray};
        holder.push_back(c);
      }
      image_.push_back(holder);
    }
  }
  width_ = image_.at(0).size();
  height_ = image_.size();
}

GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t width,
                               size_t height) {
  ElevationDataset dataset = {filename, width, height};
  if (dataset.max_ele() == dataset.min_ele()) {
    for (int i = 0; i < (int)height; i++) {
      std::vector<Color> holder;
      for (int j = 0; j < (int)width; j++) {
        int shade_of_gray = 0;
        Color c = {shade_of_gray, shade_of_gray, shade_of_gray};
        holder.push_back(c);
      }
      image_.push_back(holder);
    }
  } else {
    for (auto row : dataset.get_data()) {
      std::vector<Color> holder;
      for (auto x : row) {
        double shade =
            255.0 * ((double)(x - dataset.min_ele()) /
                     (double)(dataset.max_ele() - dataset.min_ele()));
        int shade_of_gray = std::round(shade);
        // std::cout << shade_of_gray << std::endl;
        Color c = {shade_of_gray, shade_of_gray, shade_of_gray};
        holder.push_back(c);
      }
      image_.push_back(holder);
    }
  }
  width_ = width;
  height_ = height;
}

// PPM
void GrayscaleImage::to_ppm(const std::string& name) const {
  // std::ofstream(name);
  // std::ofstream output(name + ".ppm", std::ofstream::out);
  std::ofstream output(name);
  output << "P3"
         << "\n";
  output << width_ << ' ' << height_ << "\n";
  output << "255"
         << "\n";
  for (auto row : image_) {
    for (auto x : row) {
      output << x.red() << ' ' << x.green() << ' ' << x.blue() << ' ';
    }
    output << "\n";
  }
  output << std::endl;
  // output.close();
}