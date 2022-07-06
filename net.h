#pragma once

#include <iostream>
#include <random>
#include <limits>

inline void matmul_l1(float *input, float *w, float *output);
inline void matmul_l2(float *input, float *w, float *output);
inline void matmul_l3(float *input, float *w, float *output);
inline void relu_l1(float *x);
inline void relu_l2(float *x);

struct nnet {
  float *w1;
  float *w2;
  float *w3;
  bool is_ready = false;
};

nnet *create_nnet();
nnet *create_nnet_from_params(float *w1, float *w2, float *w3);
void destroy_params(nnet *net);

int forward(nnet *net, float *x);
