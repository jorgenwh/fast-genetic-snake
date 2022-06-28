#include <random>
#include <limits>

#include "net.h"

inline void matmul(float *A, float *B, float *C, int Ar, int Ac, int Bc) {
  for (int i = 0; i < Ar; i++) {
    for (int j = 0; j < Bc; j++) {
      for (int k = 0; k < Ac; k++) {
        C[i*Bc + j] += A[i*Ac + k] * B[k*Bc + j];
      }
    }
  }
}

inline void relu(float *x, int size) {
  for (int i = 0; i < size; i++) {
    x[i] = (x[i] > 0) ? x[i] : 0;
  }
}

Net::Net() {
  w1 = new float[640];
  w2 = new float[240];
  w3 = new float[48];
}

Net::Net(float *w1, float *w2, float *w3) {
  this->w1 = w1;
  this->w2 = w2;
  this->w3 = w3;
}

Net::~Net() {
  delete[] w1;
  delete[] w2;
  delete[] w3;
}

int Net::forward(float *x) {
  float *z1 = new float[20];
  float *z2 = new float[12];
  float *out = new float[4];

  matmul(x, w1, z1, 32, 1, 20);
  relu(z1, 20);
  matmul(z1, w2, z2, 20, 1, 12);
  relu(z2, 12);
  matmul(z2, w3, out, 12, 1, 4);

  int action = 0;
  float max = -std::numeric_limits<float>::max();
#pragma unroll
  for (int i = 0; i < 4; i++) {
    if (out[i] > max) {
      max = out[i];
      action = i;
    }
  }

  delete[] z1;
  delete[] z2;
  delete[] out;

  return action;
}

