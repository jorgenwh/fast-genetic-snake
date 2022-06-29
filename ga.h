#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

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
  std::vector<Individual*> population;

  int snake_size;
  int num_children;
  int num_parents;
  int population_size;

  std::mutex fetch_individual_mutex;
  std::mutex count_individual_mutex;

  std::vector<SnakeEnv*> envs;

  void evaluate_individual(Individual *ind);
  void evaluate_individuals();
  void thread_worker();

  Individual *fetch_individual();
  void count_individual();
};
