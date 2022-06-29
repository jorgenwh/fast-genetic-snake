#pragma once

#include <algorithm>
#include <random>
#include <vector>

#include "net.h"
#include "individual.h"

std::vector<Individual*> elitist_selection(std::vector<Individual*> &population, int n);
std::vector<Individual*> roulette_wheel_selection(std::vector<Individual*> &population, int n);

Individual *crossover(Individual *mom, Individual *dad);

float *simulated_binary_crossover(float *mom, float *dad, int size);
float *single_point_crossover(float *mom, float *dad, int size);

void mutate(Individual *ind);

void gaussian_mutation(float *params);
