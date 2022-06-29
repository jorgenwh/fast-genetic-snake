#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#include "snake_env.h"
#include "net.h"
#include "individual.h"
#include "functional.h"

#define NUM_THREADS 1

class GA {
public:
  GA(int snake_size, int population_size);
  ~GA();

  void start();

private:
  std::vector<Individual*> population;

  int snake_size;
  int num_children;
  int num_parents;
  int population_size;

  std::mutex evaluate_individual_mutex;

  std::vector<SnakeEnv*> envs;

  int individuals_evaluated;

  void evaluate_individual(Individual *ind, SnakeEnv *env);
  void evaluate_individuals();
  void thread_worker(int id);

  Individual *fetch_individual();
  void count_individual();
};
