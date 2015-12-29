#ifndef ARGS_H
#define ARGS_H

#define INIT_WIDTH 1.0
#define MAX_STEPS 1000
#define MIN_ADAPT 100

typedef struct {
  int designUniqueN, idx, target_type;
  double A, B, C, D, G, m, rate, scale, shape, sumDiff, upperbound, width, x, x0;
} args_t;

#endif // ARGS_H
