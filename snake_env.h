#pragma once

#include <random>

enum flags {
	FLAG_ALIVE,
	FLAG_DEAD,
	FLAG_WON
};

struct observation {
	float state[32];
	int reward;
	int flag;
};

class SnakeEnv {
public:
	SnakeEnv(int size);
	~SnakeEnv();

	observation *step(int action);
	observation *reset();

private:
	int score = 0;
	int steps = 0;
	int steps_since_food = 0;

	int size;

	int head_direction;
	int tail_direction;

	int flag = FLAG_ALIVE;

	int *snake;
	int food[2];

	void set_food();

	std::mt19937 *rng;
	std::uniform_int_distribution<std::mt19937::result_type> *dist;
};

