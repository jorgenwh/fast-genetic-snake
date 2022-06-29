#include <iostream>
#include <limits>
#include <algorithm>

#include "individual.h"
#include "net.h"

Individual::Individual() {
  this->net = new Net();
}

Individual::Individual(Net *net) {
  this->net = net;
}

Individual::~Individual() {
  delete net;
}

int Individual::act(float *state) {
  return this->net->forward(state);
}

void Individual::compute_fitness(float score, float steps) {
  fitness = steps * std::pow(2.0f, score) - (steps * std::pow(2.0f, std::max(score - 2.25f, 0.0f))) + std::pow(score, 3.5f);
}

