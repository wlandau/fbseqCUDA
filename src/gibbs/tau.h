#ifndef GIBBS_TAU_H
#define GIBBS_TAU_H

__global__ void tau_kernel1(chain_t *dd){
  int id = IDX;
  if(id < dd->G)
    dd->aux[id] = 1.0/dd->gamma[id];
}

__global__ void tau_kernel2(chain_t *dd){
  args_t args;
  args.idx = 0;
  args.m = dd->m;
  args.sumDiff = dd->tauSumDiff[0];
  args.target_type = LTARGET_GAMMA;
  args.width = dd->tauWidth[0];
  args.x0 = dd->tau[0];

  args.shape = dd->a[0] + 0.5 * dd->G * dd->nu[0];
  args.rate = dd->b[0] + 0.5 * dd->nu[0] * dd->aux[0];
  args.upperbound = CUDART_INF;

  args = slice(dd, args);
  dd->tau[0] = args.x;
  dd->tauSumDiff[0] = args.sumDiff;
  dd->tauWidth[0] = args.width;
}

void tauSample(SEXP hh, chain_t *hd, chain_t *dd){
  if(!(vi(le(hh, "parameter_sets_update"), "tau"))) return;

  tau_kernel1<<<GRID, BLOCK>>>(dd);

  thrust::device_ptr<double> tmp(hd->aux);
  double sum = thrust::reduce(tmp, tmp + li(hh, "G")[0]);
  CUDA_CALL(cudaMemcpy(hd->aux, &sum, sizeof(double), cudaMemcpyHostToDevice));

  tau_kernel2<<<1, 1>>>(dd);
}

#endif // GIBBS_TAU_H
