#include <iostream>
#include "JSON.hpp"

int main(int argc, char **argv) {
  JSON obj("{\"name\":\"Seth Peden\"}");
  std::cout << obj["name"] << std::endl;
  obj["name"] = "Ethan Peden";
  std::cout << obj["name"] << std::endl;
  return 0;
}
