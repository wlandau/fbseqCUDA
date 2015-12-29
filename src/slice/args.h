#ifndef SLICE_ARGS_H
#define SLICE_ARGS_H

typedef struct {
  int designUniqueN, idx, target_type;
  double A, B, C, D, G, m, rate, scale, shape, sumDiff, upperbound, width, x, x0;
} args_t;

#endif // SLICE_ARGS_H
