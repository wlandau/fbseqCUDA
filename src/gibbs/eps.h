#ifndef EPS_H
#define EPS_H

__global__ void eps_kernel1(chain_t *dd){
  int n = IDX, g = IDY;
  if(n >= dd->N || g >= dd->G)
    return;

  approx_gibbs_args_t args;
  args.idx = I(n, g);
  args.target_type = LTARGET_BASIC;
  args.step_width = 1.0;
  args.max_steps = 30;
  args.A = (double) dd->counts[I(n, g)];
  args.B = 1.0/(2.0 * dd->rho[n] * dd->rho[n] * dd->gam[g] * dd->gam[g]);
  args.C = 0.0;
  args.D = exp(eta(dd, n, g));
  args.E = 0.0;
  args.x0 = dd->eps[I(n, g)];
  dd->eps[I(n, g)] = stepping_out_slice(dd, args);
}

void epsSample(SEXP hh, chain_t *hd, chain_t *dd){
  if(!(vi(le(hh, "updates"), "eps"))) return;
  dim3 grid(GRID_N, GRID_G), block(BLOCK_N, BLOCK_G);
  eps_kernel1<<<grid, block>>>(dd);
}

#endif // EPS_H
