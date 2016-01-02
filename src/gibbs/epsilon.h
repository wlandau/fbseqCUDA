#ifndef GIBBS_EPSILON_H
#define GIBBS_EPSILON_H

__global__ void epsilon_kernel1(chain_t *dd, int sampler){
  int n, g;

  for(n = IDY; n < dd->N; n += NTHREADSY){
    for(g = IDX; g < dd->G; g += NTHREADSX){

      args_t args;
      args.idx = I(n, g);
      args.lowerbound = -CUDART_INF;
      args.m = dd->m;
      args.sampler = sampler;
      args.tuneAux = dd->epsilonTuneAux[I(n, g)];
      args.target_type = LTARGET_EPSILON;
      args.tune = dd->epsilonTune[I(n, g)];
      args.upperbound = CUDART_INF;
      args.x0 = dd->epsilon[I(n, g)];

      args.A = (double) dd->counts[I(n, g)];
      args.B = 1.0/(2.0 * dd->gamma[g]);
      args.C = 0.0;
      args.D = exp(dd->h[n] + Xbeta(dd, n, g));

      args = sampler_wrap(dd, args);
      dd->epsilon[I(n, g)] = args.x;
      dd->epsilonTune[I(n, g)] = args.tune;
      dd->epsilonTuneAux[I(n, g)] = args.tuneAux;
    }
  }
}

void epsilonSample(SEXP hh, chain_t *hd, chain_t *dd){
  if(!(vi(le(hh, "parameter_sets_update"), "epsilon"))) return;
  dim3 grid(GRID_G, GRID_N), block(BLOCK_G, BLOCK_N);
  epsilon_kernel1<<<grid, block>>>(dd, li(hh, "epsilonSampler")[0]);
}

#endif // GIBBS_EPSILON_H
