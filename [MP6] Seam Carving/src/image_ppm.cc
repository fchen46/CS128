#include "image_ppm.hpp"

// implement the rest of ImagePPM's functions here

Pixel ImagePPM::GetPixel(int row, int col) const { return pixels_[row][col]; }

int ImagePPM::GetMaxColorValue() const { return max_color_value_; }

std::ostream& operator<<(std::ostream& os, const ImagePPM& image) {
  os << "P3"
     << "\n";
  os << image.GetWidth() << ' ' << image.GetHeight() << "\n";
  os << image.GetMaxColorValue() << "\n";
  for (int row = 0; row < image.GetHeight(); row++) {
    for (int col = 0; col < image.GetWidth(); col++) {
      Pixel p = image.GetPixel(row, col);
      os << p.GetRed() << "\n";
      os << p.GetGreen() << "\n";
      os << p.GetBlue() << "\n";
    }
  }
  return os;
}

// helper - vertical
void ImagePPM::CarveVerticalSeam(int* path) {
  // initialize new pixels array
  Pixel** NewPixels_ = new Pixel*[height_];
  for (int row = 0; row < height_; row++) {
    NewPixels_[row] = new Pixel[width_ - 1];
  }
  // move original pixels to the new pixels array
  for (int row = 0; row < height_; row++) {
    int colCounter = 0;
    for (int col = 0; col < width_; col++) {
      if (col != path[row]) {
        NewPixels_[row][colCounter] = pixels_[row][col];
        colCounter += 1;
      }
    }
  }
  // clear original pixels_
  int h = height_;
  int w = width_ - 1;
  Clear();
  // update pixels_ to new
  height_ = h;
  width_ = w;
  // initialize an empty pixels with new dimensions
  pixels_ = new Pixel*[height_];
  for (int i = 0; i < height_; i++) {
    pixels_[i] = new Pixel[width_];
  }
  // populate new empty pixels
  for (int i = 0; i < height_; i++) {
    for (int j = 0; j < width_; j++) {
      pixels_[i][j] = NewPixels_[i][j];
    }
  }
  // clean NewPixels_
  for (int j = 0; j < height_; ++j) {
    delete[] NewPixels_[j];
  }
  delete[] NewPixels_;
}

// helper - horizontal
void ImagePPM::CarveHorizontalSeam(int* path) {
  // initialize new pixels array
  Pixel** NewPixels_ = new Pixel*[height_ - 1];
  for (int row = 0; row < height_ - 1; row++) {
    NewPixels_[row] = new Pixel[width_];
  }
  // move original pixels to the new pixels array
  for (int col = 0; col < width_; col++) {
    int rowCounter = 0;
    for (int row = 0; row < height_; row++) {
      if (row != path[col]) {
        NewPixels_[rowCounter][col] = pixels_[row][col];
        rowCounter += 1;
      }
    }
  }

  // clear original pixels_
  int h = height_ - 1;
  int w = width_;
  Clear();
  // update pixels_ to new
  height_ = h;
  width_ = w;
  // initialize an empty pixels with new dimensions
  pixels_ = new Pixel*[height_];
  for (int i = 0; i < height_; i++) {
    pixels_[i] = new Pixel[width_];
  }

  // populate new empty pixels
  for (int i = 0; i < height_; i++) {
    for (int j = 0; j < width_; j++) {
      pixels_[i][j] = NewPixels_[i][j];
    }
  }

  // clean NewPixels_
  for (int j = 0; j < height_; ++j) {
    delete[] NewPixels_[j];
  }
  delete[] NewPixels_;
}

// // method 2
// void ImagePPM::CarveVerticalSeam(int* path) {
//   for (int row = 0; row < height_; row++) {
//     for (int col = 0; col < width_; col++) {
//       if (col == width_ - 1) {
//         break;
//       }
//       if (col >= path[row]) {
//         pixels_[row][col] = pixels_[row][col + 1];
//       } else {
//         pixels_[row][col] = pixels_[row][col];
//       }
//     }
//   }
//   width_ -= 1;
//   height_ -= 0;
// }

// void ImagePPM::CarveHorizontalSeam(int* path) {
//   for (int col = 0; col < width_; col++) {
//     for (int row = 0; row < height_; row++) {
//       if (row == height_ - 1) {
//         break;
//       }
//       if (row >= path[col]) {
//         pixels_[row][col] = pixels_[row + 1][col];
//       } else {
//         pixels_[row][col] = pixels_[row][col];
//       }
//     }
//   }
//   width_ -= 0;
//   height_ -= 1;
// }

// given functions below, DO NOT MODIFY

ImagePPM::ImagePPM() {
  height_ = 0;
  width_ = 0;
  max_color_value_ = 0;
  pixels_ = nullptr;
}

ImagePPM::ImagePPM(const std::string& path) {
  height_ = 0;
  width_ = 0;
  max_color_value_ = 0;
  pixels_ = nullptr;

  std::ifstream input_file(path);
  input_file >> *this;
  input_file.close();
}

ImagePPM::ImagePPM(const ImagePPM& source) {
  height_ = 0;
  width_ = 0;
  max_color_value_ = 0;
  pixels_ = nullptr;

  *this = source;
}

ImagePPM& ImagePPM::operator=(const ImagePPM& source) {
  if (this == &source) {
    return *this;
  }

  Clear();

  height_ = source.height_;
  width_ = source.width_;
  max_color_value_ = source.max_color_value_;

  pixels_ = new Pixel*[height_];
  for (int row = 0; row < height_; row++) {
    pixels_[row] = new Pixel[width_];

    for (int col = 0; col < width_; col++) {
      pixels_[row][col] = source.pixels_[row][col];
    }
  }

  return *this;
}

ImagePPM::~ImagePPM() { Clear(); }

void ImagePPM::Clear() {
  for (int i = 0; i < height_; i++) {
    delete[] pixels_[i];
  }

  delete[] pixels_;

  height_ = 0;
  width_ = 0;
  pixels_ = nullptr;
}

std::istream& operator>>(std::istream& is, ImagePPM& image) {
  image.Clear();
  std::string line;

  // ignore magic number line
  getline(is, line);

  // check to see if there's a comment line
  getline(is, line);
  if (line[0] == '#') {
    getline(is, line);
  }

  // parse width and height
  int space = line.find_first_of(' ');
  image.width_ = std::stoi(line.substr(0, space));
  image.height_ = std::stoi(line.substr(space + 1));

  // get max color value
  getline(is, line);
  image.max_color_value_ = std::stoi(line);

  // init and fill in Pixels array
  image.pixels_ = new Pixel*[image.height_];
  for (int i = 0; i < image.height_; i++) {
    image.pixels_[i] = new Pixel[image.width_];
  }

  for (int row = 0; row < image.height_; row++) {
    for (int col = 0; col < image.width_; col++) {
      getline(is, line);
      int red = std::stoi(line);
      getline(is, line);
      int green = std::stoi(line);
      getline(is, line);
      int blue = std::stoi(line);

      Pixel p(red, green, blue);
      image.pixels_[row][col] = p;
    }
  }

  return is;
}
