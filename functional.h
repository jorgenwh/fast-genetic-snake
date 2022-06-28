#pragma once

#include <algorithm>
#include <random>
#include <vector>

#include "net.h"
#include "individual.h"

std::vector<Individual> elitist_selection(std::vector<Individual> &population, int n);
