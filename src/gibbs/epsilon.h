#ifndef EPSILON_H
#define EPSILON_H

__global__ void epsilon_kernel1(chain_t *dd){
  int n = IDX, g = IDY;
  if(n >= dd->N || g >= dd->G)
    return;

  args_t args;
  args.idx = I(n, g);
  args.target_type = LTARGET_BASIC;
  args.step_width = 1.0;
  args.max_steps = 30;
  args.A = (double) dd->counts[I(n, g)];
  args.B = 1.0/(2.0 * dd->rho[n] * dd->gamma[g]);
  args.C = 0.0;
  args.D = exp(Xbeta(dd, n, g));
  args.E = 0.0;
  args.x0 = dd->epsilon[I(n, g)];
  dd->epsilon[I(n, g)] = slice(dd, args);
}

void epsilonSample(SEXP hh, chain_t *hd, chain_t *dd){
  if(!(vi(le(hh, "parameter_sets_update"), "epsilon"))) return;
  dim3 grid(GRID_N, GRID_G), block(BLOCK_N, BLOCK_G);
  epsilon_kernel1<<<grid, block>>>(dd);
}

#endif // EPSILON_H
