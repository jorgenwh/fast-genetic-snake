#include <iostream>
#include <chrono>
#include <vector>
#include <random>

#include "ga.h"
#include "snake_env.h"

int main(int argc, char **argv) {
  GA ga(10, 100);

  auto t1 = std::chrono::high_resolution_clock::now();
  ga.start(1);
  auto t2 = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
  std::cout << elapsed << std::endl;

  return EXIT_SUCCESS;
}
