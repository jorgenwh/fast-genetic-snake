#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#include "snake_env.h"
#include "net.h"
#include "individual.h"
#include "functional.h"
#include "ga.h"

GA::GA(int snake_size, int num_parents, int num_children) {
  this->snake_size = snake_size;
  this->num_parents = num_parents;
  this->num_children = num_children;
  population_size = num_parents + num_children;

  std::cout << "Initializing snake environments" << std::endl;
  for (int i = 0; i < NUM_THREADS; i++) {
    SnakeEnv *env = new SnakeEnv(snake_size);
    envs.push_back(env);
  }

  std::cout << "Initializing first generation of individuals" << std::endl;
  for (int i = 0; i < population_size; i++) {
    Individual *ind = new Individual();
    population.push_back(ind);
  }
}

GA::~GA() {
  std::cout << "Deleting environments" << std::endl;
  for (auto &env : envs) { delete env; }
  std::cout << "Deleting population" << std::endl;
  for (auto &ind : population) { delete ind; }
}

void GA::start() {
  evaluate_individuals();
}

void GA::evaluate_individual(Individual *ind) {
  ;
}

void GA::evaluate_individuals() {
  std::vector<std::thread> threads(NUM_THREADS);
  for (int i = 0; i < NUM_THREADS; i++) {
    threads[i] = std::thread(&GA::thread_worker, this);
  }
  for (auto &thread : threads) {
    if (thread.joinable()) { thread.join(); }
  }
}

void GA::thread_worker() {
  std::cout << "Thread started" << std::endl;
}
