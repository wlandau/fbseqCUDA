#ifndef GAMMA_H
#define GAMMA_H

__global__ void gamma_kernel1(chain_t *dd){
  int n = 0, g = IDX;
  double sum = 0.0, z;
  if(g >= dd->G) return;

  for(n = 0; n < dd->N; ++n){
    z = dd->epsilon[I(n, g)];
    sum += z * z;
  }

  args_t args;
  args.idx = g;
  args.x0 = dd->gamma[g];
  args.target_type = LTARGET_INV_GAMMA;
  args.step_width = STEP_WIDTH;
  args.max_steps = MAX_STEPS;
  args.shape = 0.5 * (dd->N + dd->nu[0]);
  args.scale = 0.5 * (dd->nu[0] * dd->tau[0] + sum);
  args.upperbound = CUDART_INF;

  dd->gamma[g] = slice(dd, args);
}

void gammaSample(SEXP hh, chain_t *hd, chain_t *dd){
  if(!(vi(le(hh, "parameter_sets_update"), "gamma"))) return;
  gamma_kernel1<<<GRID, BLOCK>>>(dd);
}

#endif // GAMMA_H
