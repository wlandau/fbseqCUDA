#ifndef EPSILON_H
#define EPSILON_H

__global__ void epsilon_kernel1(chain_t *dd){
  int n = IDX, g = IDY;
  if(n >= dd->N || g >= dd->G)
    return;

  args_t args;
  args.idx = I(n, g);
  args.m = dd->m;
  args.sumDiff = dd->epsilonSumDiff[I(l, g)];
  args.target_type = LTARGET_EPSILON;
  args.width = dd->epsilonWidth[I(n, g)];
  args.x0 = dd->epsilon[I(n, g)];

  args.A = (double) dd->counts[I(n, g)];
  args.B = 1.0/(2.0 * dd->gamma[g]);
  args.C = 0.0;
  args.D = exp(dd->h[n] + Xbeta(dd, n, g));

  args = = slice(dd, args);
  dd->epsilon[I(n, g)] = args.x;
  dd->epsilonSumDiff[I(l, g)] = args.sumDiff;
  dd->epsilonWidth[I(n, g)] = args.width;
}

void epsilonSample(SEXP hh, chain_t *hd, chain_t *dd){
  if(!(vi(le(hh, "parameter_sets_update"), "epsilon"))) return;
  dim3 grid(GRID_N, GRID_G), block(BLOCK_N, BLOCK_G);
  epsilon_kernel1<<<grid, block>>>(dd);
}

#endif // EPSILON_H
