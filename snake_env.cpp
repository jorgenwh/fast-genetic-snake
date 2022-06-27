#include <random>
#include <algorithm>

#include "snake_env.h"

SnakeEnv::SnakeEnv(int size) {
	this->size = size;

	std::random_device rdev;	
	rng = new std::mt19937(rdev());
	dist = new std::uniform_int_distribution<std::mt19937::result_type>(0, size);


}
