#include "seam_carver.hpp"

#include <iostream>

// implement the rest of SeamCarver's functions here

// Returns the instance’s image
const ImagePPM& SeamCarver::GetImage() const { return image_; }
// Returns the height of the instance’s image
int SeamCarver::GetHeight() const { return height_; }
// Returns the width of the instance’s image
int SeamCarver::GetWidth() const { return width_; }

// Returns the energy of the pixel at (row, col) of the instance’s image
int SeamCarver::GetEnergy(int row, int col) const {
  // index follows: left, right, top, bottom
  Pixel left, right, top, bottom;
  // left adjacent
  if (col == 0) {
    left = image_.GetPixel(row, image_.GetWidth() - 1);
  } else {
    left = image_.GetPixel(row, col - 1);
  }
  // right adjacent
  if (col == image_.GetWidth() - 1) {
    right = image_.GetPixel(row, 0);
  } else {
    right = image_.GetPixel(row, col + 1);
  }
  // top adjacent
  if (row == 0) {
    top = image_.GetPixel(image_.GetHeight() - 1, col);
  } else {
    top = image_.GetPixel(row - 1, col);
  }
  // bottom adjacent
  if (row == image_.GetHeight() - 1) {
    bottom = image_.GetPixel(0, col);
  } else {
    bottom = image_.GetPixel(row + 1, col);
  }
  // row energy - left & right
  int rowEnergy =
      (left.GetBlue() - right.GetBlue()) * (left.GetBlue() - right.GetBlue()) +
      (left.GetGreen() - right.GetGreen()) *
          (left.GetGreen() - right.GetGreen()) +
      (left.GetRed() - right.GetRed()) * (left.GetRed() - right.GetRed());
  int colEnergy =
      (top.GetBlue() - bottom.GetBlue()) * (top.GetBlue() - bottom.GetBlue()) +
      (top.GetGreen() - bottom.GetGreen()) *
          (top.GetGreen() - bottom.GetGreen()) +
      (top.GetRed() - bottom.GetRed()) * (top.GetRed() - bottom.GetRed());
  return rowEnergy + colEnergy;
}

// Returns the horizontal seam of image_ with the least amount of energy
int* SeamCarver::GetHorizontalSeam() const {
  // Initialize SeamVals
  int** SeamVals = new int*[height_];
  for (int row = 0; row < height_; ++row) {
    SeamVals[row] = new int[width_];
  }
  // Last column of SeamVals - directly get the energy from last row of image
  for (int row = 0; row < height_; row++) {
    SeamVals[row][width_ - 1] = GetEnergy(row, width_ - 1);
  }
  // Each new column depends on the previous column
  for (int col = width_ - 2; col >= 0; col--) {
    for (int row = 0; row < height_; row++) {
      // first row
      if (row == 0) {
        int first = SeamVals[row][col + 1];
        int second = SeamVals[row + 1][col + 1];
        SeamVals[row][col] = GetEnergy(row, col) + std::min(first, second);
      }
      // last column
      else if (row == height_ - 1) {
        int first = SeamVals[row - 1][col + 1];
        int second = SeamVals[row][col + 1];
        SeamVals[row][col] = GetEnergy(row, col) + std::min(first, second);
      }
      // middle columns
      else {
        int first = SeamVals[row - 1][col + 1];
        int second = SeamVals[row][col + 1];
        int third = SeamVals[row + 1][col + 1];
        SeamVals[row][col] =
            GetEnergy(row, col) + GetMinVal(first, second, third);
      }
    }
  }
  // Extract minimum seam path from SeamVals
  int* SeamPath = new int[width_];
  // The first index is the smallest seamval in the first column
  int minHolder = SeamVals[0][0];
  int minRowNumber = 0;
  for (int i = 0; i < height_; i++) {
    if (SeamVals[i][0] < minHolder) {
      minHolder = SeamVals[i][0];
      minRowNumber = i;
    }
  }
  SeamPath[0] = minRowNumber;
  // Loop through the other columns to find minimum change in energy
  // i is the same as row here
  for (int i = 0; i < width_ - 1; i++) {
    // first row
    if (SeamPath[i] == 0) {
      int row = 0;
      int first = SeamVals[row][i + 1];
      int second = SeamVals[row + 1][i + 1];
      if (first <= second) {
        SeamPath[i + 1] = row;
      } else {
        SeamPath[i + 1] = row + 1;
      }
    }
    // last row
    else if (SeamPath[i] == height_ - 1) {
      int row = SeamPath[i];
      int first = SeamVals[row - 1][i + 1];
      int second = SeamVals[row][i + 1];
      if (second <= first) {
        SeamPath[i + 1] = row;
      } else {
        SeamPath[i + 1] = row - 1;
      }
    }
    // middle columns
    else {
      int row = SeamPath[i];
      int first = SeamVals[row - 1][i + 1];
      int second = SeamVals[row][i + 1];
      int third = SeamVals[row + 1][i + 1];
      if (second <= first && second <= third) {
        SeamPath[i + 1] = row;
      } else if (first <= second && first <= third) {
        SeamPath[i + 1] = row - 1;
      } else if (third <= first && third <= second) {
        SeamPath[i + 1] = row + 1;
      }
    }
  }
  // Clean Up Memory
  for (int j = 0; j < height_; ++j) {
    delete[] SeamVals[j];
  }
  delete[] SeamVals;
  // Return path
  return SeamPath;
}

// Returns the vertical seam of image_ with the least amount of energy
int* SeamCarver::GetVerticalSeam() const {
  // Initialize SeamVals
  int** SeamVals = new int*[height_];
  for (int row = 0; row < height_; ++row) {
    SeamVals[row] = new int[width_];
  }
  // Last row of SeamVals - directly get the energy from last row of image
  for (int col = 0; col < width_; col++) {
    SeamVals[height_ - 1][col] = GetEnergy(height_ - 1, col);
  }
  // Each new row depends on the previous row
  for (int row = height_ - 2; row >= 0; row--) {
    for (int col = 0; col < width_; col++) {
      // first column
      if (col == 0) {
        int first = SeamVals[row + 1][col];
        int second = SeamVals[row + 1][col + 1];
        SeamVals[row][col] = GetEnergy(row, col) + std::min(first, second);
      }
      // last column
      else if (col == width_ - 1) {
        int first = SeamVals[row + 1][col - 1];
        int second = SeamVals[row + 1][col];
        SeamVals[row][col] = GetEnergy(row, col) + std::min(first, second);
      }
      // middle columns
      else {
        int first = SeamVals[row + 1][col - 1];
        int second = SeamVals[row + 1][col];
        int third = SeamVals[row + 1][col + 1];
        SeamVals[row][col] =
            GetEnergy(row, col) + GetMinVal(first, second, third);
      }
    }
  }

  // Extract minimum seam path from SeamVals
  int* SeamPath = new int[height_];
  // int SeamPath[height_];
  // The first index is the smallest seamval in the first row
  // SeamPath[0] = GetMinVal(SeamVals[0]);
  int minHolder = SeamVals[0][0];
  int indexHolder = 0;
  for (int i = 0; i < width_; i++) {
    if (SeamVals[0][i] < minHolder) {
      minHolder = SeamVals[0][i];
      indexHolder = i;
    }
  }
  SeamPath[0] = indexHolder;
  // Loop through the other rows to find minimum change in energy
  // i is the same as row here
  for (int i = 0; i < height_ - 1; i++) {
    // first column
    if (SeamPath[i] == 0) {
      int col = 0;
      int first = SeamVals[i + 1][col];
      int second = SeamVals[i + 1][col + 1];
      if (first <= second) {
        SeamPath[i + 1] = col;
      } else {
        SeamPath[i + 1] = col + 1;
      }
    }
    // last column
    else if (SeamPath[i] == width_ - 1) {
      int col = SeamPath[i];
      int first = SeamVals[i + 1][col - 1];
      int second = SeamVals[i + 1][col];
      if (second <= first) {
        SeamPath[i + 1] = col;
      } else {
        SeamPath[i + 1] = col - 1;
      }
    }
    // middle columns
    else {
      int col = SeamPath[i];
      int first = SeamVals[i + 1][col - 1];
      int second = SeamVals[i + 1][col];
      int third = SeamVals[i + 1][col + 1];
      if (second <= first && second <= third) {
        SeamPath[i + 1] = col;
      } else if (first <= second && first <= third) {
        SeamPath[i + 1] = col - 1;
      } else if (third <= first && third <= second) {
        SeamPath[i + 1] = col + 1;
      }
    }
  }
  // Clean Up Memory
  for (int j = 0; j < height_; ++j) {
    delete[] SeamVals[j];
  }
  delete[] SeamVals;
  // Return path
  return SeamPath;
}

// Removes one horizontal seam in image_
void SeamCarver::RemoveHorizontalSeam() {
  auto SeamToRemove = GetHorizontalSeam();
  image_.CarveHorizontalSeam(SeamToRemove);
  height_ -= 1;
  width_ -= 0;
  delete[] SeamToRemove;
}

// Removes one vertical seam in image_
void SeamCarver::RemoveVerticalSeam() {
  auto SeamToRemove = GetVerticalSeam();
  image_.CarveVerticalSeam(SeamToRemove);
  width_ -= 1;
  height_ -= 0;
  delete[] SeamToRemove;
}

// Helper
int SeamCarver::GetMinVal(int first, int second, int third) const {
  int minHolder = first;
  int arr[3] = {first, second, third};
  for (int i = 0; i < 3; i++) {
    if (arr[i] < minHolder) {
      minHolder = arr[i];
    }
  }
  return minHolder;
}

int SeamCarver::GetMinVal(int arr[]) const {
  int minHolder = arr[0];
  int indexHolder = 0;
  for (int i = 0; i < (int)sizeof(*arr); i++) {
    if (arr[i] < minHolder) {
      minHolder = arr[i];
      indexHolder = i;
    }
  }
  return indexHolder;
}

// given functions below, DO NOT MODIFY

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}
