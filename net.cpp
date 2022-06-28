#include <random>

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
	;
}

Net::~Net() {
	;
}


