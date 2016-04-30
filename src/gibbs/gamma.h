#ifndef GIBBS_GAMMA_H
#define GIBBS_GAMMA_H

void gamma_kernel1(chain_t *dd, int sampler){
  int n, g;
  double sum, z;

  for(g = IDX; g < dd->G; g += NTHREADSX){

    sum = 0.0;
    for(n = 0; n < dd->N; ++n){
      z = dd->epsilon[I(n, g)];
      sum += z * z;
    }

    args_t args;
    args.idx = g;
    args.lowerbound = 0.0;
    args.m = dd->m;
    args.sampler = sampler;
    args.tuneAux = dd->gammaTuneAux[g];
    args.target_type = LTARGET_INV_GAMMA;
    args.tune = dd->gammaTune[g];
    args.upperbound = INFINITY;
    args.x0 = dd->gamma[g];

    args.shape = 0.5 * (dd->N + dd->nu[0]);
    args.scale = 0.5 * (dd->nu[0] * dd->tau[0] + sum);

    args = sampler_wrap(dd, args);
    dd->gamma[g] = args.x;
    dd->gammaTune[g] = args.tune;
    dd->gammaTuneAux[g] = args.tuneAux;
  }
}

void gammaSample(SEXP hh, chain_t *hd, chain_t *dd){
  if(!(vi(le(hh, "parameter_sets_update"), "gamma"))) return;
  gamma_kernel1(dd, li(hh, "gammaSampler")[0]);
}

#endif // GIBBS_GAMMA_H
