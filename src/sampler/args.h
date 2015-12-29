#ifndef SAMPLER_ARGS_H
#define SAMPLER_ARGS_H

typedef struct {
  int designUniqueN, idx, sampler, target_type;
  double A, B, C, D, G, lowerbound, m, rate, scale, shape, tune, tuneAux, upperbound, x, x0;
} args_t;

#endif // SAMPLER_ARGS_H
