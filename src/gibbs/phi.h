#ifndef PHI_H
#define PHI_H

__global__ void phi_kernel1(chain_t *dd){
  int g = IDX, n;
  double D0[3] = {0.0, 0.0, 0.0};

  if(g >= dd->G)
    return;

  approx_gibbs_args_t args;
  args.idx = g;
  args.x0 = dd->phi[g];
  args.target_type = LTARGET_BASIC;
  args.step_width = STEP_WIDTH;
  args.max_steps = MAX_STEPS;

  args.A = (double) dd->sums_g[g];
  args.B = 1.0/(2.0 * dd->sigPhi[0] * dd->sigPhi[0] * dd->xiPhi[g]);
  args.C = dd->thePhi[0];

  for(n = 0; n < dd->N; ++n)
    D0[dd->group[n] - 1] += exp(dd->eps[I(n, g)]);

  args.D = exp( dd->alp[g] - dd->del[g]) * D0[0]
         + exp(-dd->alp[g] + dd->del[g]) * D0[1]
         + exp( dd->alp[g] + dd->del[g]) * D0[2];
  args.E = 0.0;

  dd->phi[g] = stepping_out_slice(dd, args);
}

void phiSample(SEXP hh, chain_t *hd, chain_t *dd){
  if(!(vi(le(hh, "updates"), "phi"))) return;
  phi_kernel1<<<GRID, BLOCK>>>(dd);
}

#endif // PHI_H
