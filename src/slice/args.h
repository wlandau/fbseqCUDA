#ifndef ARGS_H
#define ARGS_H

#define MAX_STEPS 300
#define STEP_WIDTH 5.0

typedef struct {
  int designUniqueN, idx, max_steps, step_width, target_type;
  double A, B, C, D, G, rate, scale, shape, upperbound, x, x0;
} args_t;

#endif // ARGS_H
