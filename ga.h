#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#include "snake_env.h"
#include "net.h"
#include "functional.h"

#define NUM_THREADS 1

class GA {
public:
  GA(int snake_size, int population_size);
  ~GA();

  void start(int generations);

private:
  int snake_size;
  int population_size;

  SnakeEnv **environments;

  nnet **population;
  float *fitness_scores;

  std::mutex eval_mutex;
  int eval_counter;

  void update_population();

  void evaluate_individuals();
  void thread_worker(int id);

  int fetch_individual_index();
  void evaluate_individual(int thread_idx, int eval_index);
};
