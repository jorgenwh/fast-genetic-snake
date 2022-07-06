#pragma once

#include <algorithm>
#include <random>
#include <vector>

#include "net.h"

float compute_fitness(float score, float steps);

int partition(nnet **population, float *fitness_scores, int lo, int hi);
void quicksort(nnet **population, float *fitness_scores, int lo, int hi);

void simulated_binary_crossover(float *p1, float *p2, float *child);
nnet *crossover(nnet *p1, nnet *p2);

void gaussian_mutation(float *w);
void mutate(nnet *child);
