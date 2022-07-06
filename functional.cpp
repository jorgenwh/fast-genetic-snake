#include <algorithm>
#include <random>
#include <vector>
#include <string.h>

#include "net.h"
#include "functional.h"

float compute_fitness(float score, float steps) {
  return steps * std::pow(2.0f, score) - (steps * std::pow(2.0f, std::max(score - 2.25f, 0.0f))) + std::pow(score, 3.5f);
}

int partition(nnet **population, float *fitness_scores, int lo, int hi) {
  float pivot = fitness_scores[lo];

  int count = 0;
  for (int i = lo + 1; i <= hi; i++) {
    if (fitness_scores[i] <= pivot) { count++; }
  }

  int pind = lo + count;
  std::swap(population[pind], population[lo]);
  std::swap(fitness_scores[pind], fitness_scores[lo]);

  int i = lo;
  int j = hi;

  while (i < pind && j > pind) {
    while (fitness_scores[i] <= pivot) { i++; }
    while (fitness_scores[j] > pivot) { j--; }
    if (i < pind && j > pind) {
      std::swap(population[i], population[j]);
      std::swap(fitness_scores[i], fitness_scores[j]);
      i++;
      j--;
    }
  }

  return pind;
}

void quicksort(nnet **population, float *fitness_scores, int lo, int hi) {
  if (lo >= hi) { return; }

  int p = partition(population, fitness_scores, lo, hi);

  quicksort(population, fitness_scores, lo, p-1);
  quicksort(population, fitness_scores, p+1, hi);
}

void simulated_binary_crossover(float *p1, float *p2, float *child, int rows, int cols) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<> dist(0, rows*cols);

  int pos = dist(rng); 

  memcpy(child, p1, sizeof(float)*pos);
  memcpy(&child[pos], &p1[pos], sizeof(float)*(rows*cols - pos));
}

void single_point_crossover(float *p1, float *p2, float *child, int rows, int cols) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_real_distribution<> dist(0.0f, 1.0f);

  float rand, gamma;
  for (int i = 0; i < rows*cols; i++) {
    rand = dist(rng); 
    if (rand <= 0.5f) { gamma = 2.0f * std::pow(rand, 0.00990099f); }
    else { gamma = std::pow((1.0f / (2.0f * (1.0f - rand))), 0.00990099f); }

    rand = dist(rng);
    if (rand <= 0.5f) { child[i] = 0.5f * ((1.0f + gamma) * p1[i] + (1.0f - gamma) * p2[i]); }
    else { child[i] = 0.5f * ((1.0f - gamma) * p1[i] + (1.0f + gamma) * p2[i]); }
  }
}

nnet *crossover(nnet *p1, nnet *p2) {
  printf("1\n");
  float *w1 = new float[32*20];
  printf("2\n");
  float *w2 = new float[20*12];
  printf("3\n");
  float *w3 = new float[12*4];
  printf("4\n");

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<> dist(0, 1);

  if (dist(rng)) { simulated_binary_crossover(p1->w1, p2->w1, w1, 32, 20); }
  else { single_point_crossover(p1->w1, p2->w1, w1, 32, 20); }

  if (dist(rng)) { simulated_binary_crossover(p1->w2, p2->w2, w2, 20, 12); }
  else { single_point_crossover(p1->w3, p2->w3, w3, 20, 12); }

  if (dist(rng)) { simulated_binary_crossover(p1->w3, p2->w3, w3, 12, 4); }
  else { single_point_crossover(p1->w3, p2->w3, w3, 12, 4); }

  nnet *child = create_nnet_from_params(w1, w2, w3);
  return child;
}

void gaussian_mutation(float *w, int rows, int cols) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::normal_distribution<> normal_dist(0.0f, 1.0f);
  std::uniform_real_distribution<> dist(0.0f, 1.0f);

  for (int i = 0; i < rows*cols; i++) {
    if (dist(rng) >= 0.05f) {
      w[i] += normal_dist(rng) * 0.2f;
    }
  }
}

void mutate(nnet *child) {
  gaussian_mutation(child->w1, 32, 20);
  gaussian_mutation(child->w2, 20, 12);
  gaussian_mutation(child->w3, 12, 4);
}
