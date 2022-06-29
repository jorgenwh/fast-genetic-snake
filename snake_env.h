#pragma once

#include <deque>
#include <string>
#include <iostream>
#include <random>
#include <algorithm>

enum flags {
  FLAG_ALIVE,
  FLAG_DEAD,
  FLAG_WON
};

struct observation {
  float *state;
  float reward;
  int flag;

  ~observation() { delete[] state; }
};

struct coord {
  int x;
  int y;

  bool operator==(const coord &other) const { 
    return (x == other.x && y == other.y); 
  }
  coord &operator=(const coord &other) { 
    x = other.x;
    y = other.y;
    return *this;
  }
};

extern coord directions[4]; 
extern coord vision_directions[8];

class SnakeEnv {
public:
  SnakeEnv(int size);
  ~SnakeEnv();

  observation *step(int action);
  observation *reset();

  void print();
  int get_score() { return score; }
  int get_steps() { return steps; }

private:
  int score = 0;
  int steps = 0;
  int steps_since_food = 0;

  int size;
  int win_score;

  int head_direction;
  int tail_direction;

  int flag = FLAG_ALIVE;

  std::deque<coord> snake;
  coord food;

  std::mt19937 *rng;
  std::uniform_int_distribution<std::mt19937::result_type> *dist;

  void initialize_snake();
  void set_food();

  float *get_state();
  inline bool is_within_map(coord &pos);
  inline bool is_valid(coord &pos);
  inline bool is_backwards(int action);
};

