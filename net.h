#pragma once

#include <random>

inline void matmul(float *A, float *B, float *C, int Ar, int Bc);
inline void relu(float *x);

class Net {
public:
  Net();
  ~Net();

  float *forward(float *x);

private:
  float *w1, w2, w3;
};
