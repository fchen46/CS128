#include <iostream>

#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"
#include "path_image.hpp"

int main() {
  ElevationDataset e = {
      "/home/vagrant/src/MP/mp-mountain-paths-zorazrr/example-data/"
      "ex_input_data/map-input-w480-h480.dat",
      480,
      480};
  // for (auto row : e.get_data()) {
  //   for (auto x : row) {
  //     std::cout << x << ", ";
  //   }
  //   std::cout << "\n";
  // }
  std::cout << "max: " << e.max_ele() << std::endl;
  std::cout << "min: " << e.min_ele() << std::endl;
  GrayscaleImage gi = {e};
  gi.to_ppm("test");
  PathImage pi = {gi, e};
  // for (Path p : pi.paths()) {
  //   std::cout << p.ele_change() << std::endl;
  // }
  pi.to_ppm("colortest");
}