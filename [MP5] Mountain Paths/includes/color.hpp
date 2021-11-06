#ifndef COLOR_H
#define COLOR_H

class Color {
 public:
  Color();
  Color(int r, int g, int b);
  int red() const { return red_; }
  int green() const { return green_; }
  int blue() const { return blue_; };

 private:
  int red_;
  int green_;
  int blue_;
};

bool operator==(const Color& rhs, const Color& lhs);

#endif