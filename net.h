#pragma once

#include <random>

inline void matmul(float *A, float *B, float *C, int Ar, int Bc);
inline void relu(float *x);

struct Net {
  Net();
  Net(float *w1, float *w2, float *w3);
  ~Net();
  float *forward(float *x);
  float *w1, *w2, *w3;
};
