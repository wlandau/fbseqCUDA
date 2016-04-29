#ifndef GIBBS_TAU_H
#define GIBBS_TAU_H

__global__ void tau_kernel1(chain_t *dd){
  int g;
  for(g = IDX; g < dd->G; g += NTHREADSX){ printf("      TAU g = %d\n", g);
    dd->aux[g] = 1.0/dd->gamma[g];
  }
}

__global__ void tau_kernel2(chain_t *dd, int sampler){
  args_t args;
  args.idx = 0;
  args.lowerbound = 0.0;
  args.m = dd->m;
  args.sampler = sampler;
  args.tuneAux = dd->tauTuneAux[0];
  args.target_type = LTARGET_GAMMA;
  args.tune = dd->tauTune[0];
  args.upperbound = CUDART_INF;
  args.x0 = dd->tau[0];

  args.shape = dd->a[0] + 0.5 * dd->G * dd->nu[0];
  args.rate = dd->b[0] + 0.5 * dd->nu[0] * dd->aux[0];

  args = sampler_wrap(dd, args);
  dd->tau[0] = args.x;
  dd->tauTune[0] = args.tune;
  dd->tauTuneAux[0] = args.tuneAux;
}

void tauSample(SEXP hh, chain_t *hd, chain_t *dd){
  if(!(vi(le(hh, "parameter_sets_update"), "tau"))) return;

  tau_kernel1<<<GRID, BLOCK>>>(dd);

//  thrust::device_ptr<double> tmp(hd->aux);
//  double sum = thrust::reduce(tmp, tmp + li(hh, "G")[0]);
//  CUDA_CALL(cudaMemcpy(hd->aux, &sum, sizeof(double), cudaMemcpyHostToDevice));
  serial_reduce_aux<<<1, 1>>>(dd);

  tau_kernel2<<<1, 1>>>(dd, li(hh, "tauSampler")[0]);
}

#endif // GIBBS_TAU_H
