#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <assert.h>

#include "snake_env.h"
#include "net.h"
#include "functional.h"
#include "ga.h"

GA::GA(int snake_size, int population_size) {
  this->snake_size = snake_size;
  this->population_size = population_size; 

  environments = new SnakeEnv*[NUM_THREADS];
  for (int i = 0; i < NUM_THREADS; i++) { environments[i] = new SnakeEnv(snake_size); }

  population = new nnet*[population_size];
  for (int i = 0; i < population_size; i++) { population[i] = create_nnet(); }

  fitness_scores = new float[population_size];
}

GA::~GA() {
  for (int i = 0; i < population_size; i++) {
    destroy_params(population[i]);
    delete population[i];
  }
  for (int i = 0; i < NUM_THREADS; i++) {
    delete environments[i];
  }
  delete[] population;
  delete[] fitness_scores;
  delete[] environments;
}

void GA::start(int generations) {
  evaluate_individuals();

  for (int i = 0; i < generations; i++) {
    update_population(); 
  }
}

void GA::update_population() {
  quicksort(population, fitness_scores, 0, population_size - 1);

  // Delete the worst half of the population
  int num_children = population_size / 2;
  for (int i = 0; i < num_children; i++) {
    destroy_params(population[i]);
    delete population[i];
  }

  // Repopulate the population, randomly selecting parents from the remaining pool to create children 
  float fitness_sum = 0;
  float weights[population_size - num_children];
  for (int i = num_children; i < population_size; i++) { fitness_sum += fitness_scores[i]; }
  for (int i = num_children; i < population_size; i++) { weights[i - num_children] = fitness_scores[i] / fitness_sum; }

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_real_distribution<> dist(0.0f, 1.0f);

  for (int i = 0; i < num_children; i++) {
    nnet *p1, *p2;
    float rand1 = dist(rng); 
    float rand2 = dist(rng); 
    float offset = 0;
    bool p1_chosen = false;
    bool p2_chosen = false;

    for (int i = 0; i < population_size - num_children; i++) {
      offset += weights[i];
      if (rand1 < offset) {
        p1 = population[i + population_size - num_children];
        p1_chosen = true;
      }
      if (rand2 < offset) {
        p2 = population[i + population_size - num_children];
        p2_chosen = true;
      }
      if (p1_chosen && p2_chosen) { break; }
    }

    nnet *child = crossover(p1, p2);
    mutate(child);

    population[i] = child;
  }
}

void GA::evaluate_individuals() {
  eval_counter = 0;
  int ids[NUM_THREADS];

  std::vector<std::thread> threads(NUM_THREADS);
  for (int i = 0; i < NUM_THREADS; i++) {
    ids[i] = i;
    threads[i] = std::thread(&GA::thread_worker, this, std::ref(ids[i]));
  }
  for (auto &thread : threads) {
    if (thread.joinable()) { thread.join(); }
  }
}

void GA::thread_worker(int id) {
  int eval_idx = fetch_individual_index();

  while (eval_idx < population_size) {
    evaluate_individual(id, eval_idx);
    eval_idx = fetch_individual_index();
  }
}

int GA::fetch_individual_index() {
  std::lock_guard<std::mutex> lock(eval_mutex);
  eval_counter++;
  return eval_counter - 1;
}

void GA::evaluate_individual(int thread_idx, int eval_index) {
  SnakeEnv *env = environments[thread_idx];
  nnet *net = population[eval_index];

  observation *o = env->reset();  
  int action;

  while (o->flag == FLAG_ALIVE) {
    action = forward(net, o->state);
    delete o;
    o = env->step(action);
  }
  delete o;

  float score = (float)env->get_score();
  float steps = (float)env->get_steps();
  float fitness = compute_fitness(score, steps);

  fitness_scores[eval_index] = fitness;
}
