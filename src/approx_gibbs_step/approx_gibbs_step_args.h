#ifndef APPROX_GIBBS_STEP_ARGS_H
#define APPROX_GIBBS_STEP_ARGS_H

#define MAX_STEPS 300
#define STEP_WIDTH 5.0

typedef struct {
  int max_steps, step_width, target_type;
  double A, B, C, D, E, G, idx, rate, scale, shape, upperbound, x, x0;
} approx_gibbs_args_t;

#endif // APPROX_GIBBS_STEP_ARGS_H
