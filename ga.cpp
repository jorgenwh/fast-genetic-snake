#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#include "snake_env.h"
#include "net.h"
#include "individual.h"
#include "functional.h"
#include "ga.h"

GA::GA(int snake_size, int population_size) {
  this->snake_size = snake_size;
  this->population_size = population_size; 

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
  std::cout << "Evaluating population ..." << std::endl;
  evaluate_individuals();
}

void GA::evaluate_individual(Individual *ind, SnakeEnv *env) {
  observation *o = env->reset(); 

  int action;

  while (o->flag == FLAG_ALIVE) {
    action = ind->act(o->state);

    delete o;
    o = env->step(action);
  }
  delete o;

  float score = (float)env->get_score();
  float steps = (float)env->get_steps();
  ind->compute_fitness(score, steps);
}

void GA::evaluate_individuals() {
  individuals_evaluated = 0;

  std::vector<std::thread> threads(NUM_THREADS);
  for (int i = 0; i < NUM_THREADS; i++) {
    int id = i;
    threads[i] = std::thread(&GA::thread_worker, this, std::ref(id));
  }
  for (auto &thread : threads) {
    if (thread.joinable()) { thread.join(); }
  }
}

void GA::thread_worker(int id) {
  std::cout << "Evaluator thread " << id << " started" << std::endl;

  Individual *ind;
  do {
    ind = fetch_individual();
    evaluate_individual(ind, envs[id]);
    count_individual();
  } while (ind != nullptr);
}

Individual *GA::fetch_individual() {
  std::lock_guard<std::mutex> lock(evaluate_individual_mutex);
  Individual *ind = nullptr;

  if (individuals_evaluated < population_size) {
    ind = population[individuals_evaluated];
  }

  return ind;
}

void GA::count_individual() {
  std::lock_guard<std::mutex> lock(evaluate_individual_mutex);
  individuals_evaluated++;
  std::cout << "Individual " << individuals_evaluated << "/" << population_size << " evaluated" << std::endl;
}
