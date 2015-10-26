#ifndef GAM_H
#define GAM_H

__global__ void gam_kernel1(chain_t *dd){
  int n = 0, g = IDX;
  double sum = 0.0;

  if(g < dd->G){
    for(n = 0; n < dd->N; ++n)
      sum += dd->eps[I(n, g)]*dd->eps[I(n, g)]/(dd->rho[n]*dd->rho[n]);

    approx_gibbs_args_t args;
    args.idx = g;
    args.x0 = dd->gam[g] * dd->gam[g];
    args.target_type = LTARGET_INV_GAMMA;
    args.step_width = STEP_WIDTH;
    args.max_steps = MAX_STEPS;
    args.shape = (dd->N + dd->nuGam[0]) * 0.5;
    args.scale = 0.5 * (dd->nuGam[0] * dd->tauGam[0] * dd->tauGam[0] + sum);
    args.upperbound = CUDART_INF;

    dd->gam[g] = sqrt(stepping_out_slice(dd, args));
  }
}

void gamSample(SEXP hh, chain_t *hd, chain_t *dd){
  if(!(vi(le(hh, "updates"), "gam"))) return;
  gam_kernel1<<<GRID, BLOCK>>>(dd);
}

#endif // GAM_H
