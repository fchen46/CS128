#include "color.hpp"

#include <iostream>

Color::Color(): red_(0), green_(0), blue_(0) {}

Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  if (r < 0 || r > 255) {
    throw std::runtime_error("invalid color range red");
  } else if (g < 0 || g > 255) {
    throw std::runtime_error("invalid color range green");
  } else if (b < 0 || b > 255) {
    throw std::runtime_error("invalid color range blue");
  }
}

// do not modify: auto-grader relies on this definition of equality.
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.red() == lhs.red() && rhs.green() == lhs.green() &&
          rhs.blue() == lhs.blue());
}