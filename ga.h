#pragma once

#include <vector>

#include "snake_env.h"
#include "net.h"
#include "individual.h"
#include "functional.h"

#define NUM_THREADS 4

class GA {
public:
  GA(int snake_size, int num_parents, int num_children);
  ~GA();

  void start();

private:
  std::vector<Individual> population;

  int snake_size;
  int num_children;
  int num_parents;
  int population_size;

  void evaluate_individuals();
};
