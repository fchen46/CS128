#ifndef IMAGE_PPM_HPP
#define IMAGE_PPM_HPP

#include <fstream>
#include <iostream>
#include <string>

#include "pixel.hpp"

class ImagePPM {
public:
  // default constructor
  //
  // not tested but you are welcome to initialize (or not) member
  // variables however you like in this function
  ImagePPM();

  // overloaded constructor
  //
  // initialize the instance given the file at path. You may assume that
  // path is always valid and that a file exists at path
  ImagePPM( const std::string& path );

  // copy constructor.
  //
  // should intialize the instance as DEEP COPY of source (meaning all
  // values should be the same, but chaning source will not change
  // anything in this instance, and vice versa)
  ImagePPM( const ImagePPM& source );

  // assignment operator
  //
  // should set the instance to be a DEEP COPY of source. Note that the
  // current instance (this) already exists and you should be wary of
  // leaks and the possiblity of null pointers
  ImagePPM& operator=( const ImagePPM& source );

  // destructor
  //
  // releases all heap memory used by the instance
  ~ImagePPM();

  // returns the Pixel at row col. You may assume that row and col
  // will always be within the bounds of image_
  Pixel GetPixel( int row, int col ) const;

  // returns the width of the image
  int GetWidth() const {return width_;};

  // returns the height of the image
  int GetHeight() const {return height_;};

  // returns the max color value of the image
  int GetMaxColorValue() const;

  // outputs the image in plain PPM format to os
  friend std::ostream& operator<<( std::ostream& os, const ImagePPM& image );

  // fills in image using the input stream, is. the stream contains
  // an image in plain PPM format
  friend std::istream& operator>>( std::istream& is, ImagePPM& image );

  /**
   * Add any helper methods you may need
   */

  // helper 
  void CarveVerticalSeam(int* path);
  void CarveHorizontalSeam(int* path);

private:
  int height_;
  int width_;
  int max_color_value_;
  Pixel** pixels_;

  // given help function, "clears" the data of the instance
  void Clear();

  /**
   * Add any helper methods you may need
   */
};

#endif