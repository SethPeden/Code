#include <iostream>
#include "vector.hpp"

int main() {
  vector<double> x = {1, 2, 3, 4};
  vector<double> y = x ^ x;
  y[2] = 0;
  std::cout << y[{1, 2}] << std::endl;
  return 0;
}
