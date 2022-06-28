#pragma once

#include "net.h"

struct Individual {
  Individual();
  Individual(Net *net);
  ~Individual();

  int act(float *state);
  void compute_fitness(float score, float steps);

  Net *net;
  float fitness;
};
