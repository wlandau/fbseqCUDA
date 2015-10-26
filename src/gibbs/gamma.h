#ifndef GAMMA_H
#define GAMMA_H

__global__ void gamma_kernel1(chain_t *dd){
  int n = 0, g = IDX;
  double sum = 0.0;

  if(g < dd->G){
    for(n = 0; n < dd->N; ++n)
      sum += dd->epsilon[I(n, g)]*dd->epsilon[I(n, g)]/(dd->rho[n]*dd->rho[n]);

    approx_gibbs_args_t args;
    args.idx = g;
    args.x0 = dd->gamma[g] * dd->gamma[g];
    args.target_type = LTARGET_INV_GAMMA;
    args.step_width = STEP_WIDTH;
    args.max_steps = MAX_STEPS;
    args.shape = (dd->N + dd->nuamma[0]) * 0.5;
    args.scale = 0.5 * (dd->nuGamma[0] * dd->tauGamma[0] * dd->tauGamma[0] + sum);
    args.upperbound = CUDART_INF;

    dd->gamma[g] = slice(dd, args);
  }
}

void gammaSample(SEXP hh, chain_t *hd, chain_t *dd){
  if(!(vi(le(hh, "updates"), "gamma"))) return;
  gamma_kernel1<<<GRID, BLOCK>>>(dd);
}

#endif // GAMMA_H
