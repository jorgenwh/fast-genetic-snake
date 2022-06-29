#include <iostream>
#include <chrono>
#include <vector>

#include "ga.h"
#include "individual.h"
#include "snake_env.h"

int main(int argc, char **argv) {
  GA ga(10, 1000);
  ga.start();
  
  return EXIT_SUCCESS;
}
