#include <iostream>
#include <random>
#include <limits>

#include "net.h"

inline void matmul_l1(float *input, float *w, float *output) {
  for (int col = 0; col < 20; col++) {
    for (int i = 0; i < 32; i++) {
      output[col] += input[i] * w[col*20+i];
    }
  }
}

inline void matmul_l2(float *input, float *w, float *output) {
  for (int col = 0; col < 12; col++) {
    for (int i = 0; i < 20; i++) {
      output[col] += input[i] * w[col*12+i];
    }
  }
}

inline void matmul_l3(float *input, float *w, float *output) {
  for (int col = 0; col < 4; col++) {
    for (int i = 0; i < 12; i++) {
      output[col] += input[i] * w[col*4+i];
    }
  }
}

inline void relu_l1(float *x) {
  for (int i = 0; i < 20; i++) {
    x[i] = (x[i] > 0) ? x[i] : 0;
  }
}

inline void relu_l2(float *x) {
  for (int i = 0; i < 12; i++) {
    x[i] = (x[i] > 0) ? x[i] : 0;
  }
}

nnet *create_nnet() {
  nnet *net = new nnet();

  net->w1 = new float[32*20];
  net->w2 = new float[20*12];
  net->w3 = new float[12*4];

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_real_distribution<> dist(-1.0f, 1.0f);
  
  for (int i = 0; i < 32*20; i++) { net->w1[i] = dist(rng); }
  for (int i = 0; i < 20*12; i++) { net->w1[i] = dist(rng); }
  for (int i = 0; i < 12*4; i++) { net->w1[i] = dist(rng); }

  net->is_ready = true;

  return net;
}

nnet *create_nnet_from_params(float *w1, float *w2, float *w3) {
  nnet *net = new nnet();

  net->w1 = w1;
  net->w2 = w2;
  net->w3 = w3;

  return net;
}

void destroy_params(nnet *net) {
  delete[] net->w1;
  delete[] net->w2;
  delete[] net->w3;
}

int forward(nnet *net, float *x) {
  float *z1 = new float[20];
  float *z2 = new float[12];
  float *out = new float[4];

  matmul_l1(x, net->w1, z1);
  relu_l1(z1);
  matmul_l2(z1, net->w2, z2);
  relu_l2(z2);
  matmul_l3(z2, net->w3, out);

  int action = 0;
  float max = -std::numeric_limits<float>::max();

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
