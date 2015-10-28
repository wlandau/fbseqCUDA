#ifndef TAUGAMMA_H
#define TAUGAMMA_H

__global__ void tauGamma_kernel1(chain_t *dd){
  int id = IDX;
  if(id < dd->G)
    dd->aux[id] = 1.0/dd->gamma[id];
}

__global__ void tauGamma_kernel2(chain_t *dd){
  args_t args;
  args.idx = 0;
  args.x0 = dd->tauGamma[0];
  args.target_type = LTARGET_GAMMA;
  args.step_width = STEP_WIDTH;
  args.max_steps = MAX_STEPS;
  args.shape = dd->aGamma[0] + 0.5 * dd->G * dd->nuGamma[0];
  args.rate = dd->bGamma[0] + 0.5 * dd->nuGamma[0] * dd->aux[0];
  args.upperbound = CUDART_INF;
  dd->tauGamma[0] = slice(dd, args);
}

void tauGammaSample(SEXP hh, chain_t *hd, chain_t *dd){
  if(!(vi(le(hh, "parameter_sets_update"), "tauGamma"))) return;

  tauGamma_kernel1<<<GRID, BLOCK>>>(dd);

  thrust::device_ptr<double> tmp(hd->aux);
  double sum = thrust::reduce(tmp, tmp + li(hh, "G")[0]);
  CUDA_CALL(cudaMemcpy(hd->aux, &sum, sizeof(double), cudaMemcpyHostToDevice));

  tauGamma_kernel2<<<1, 1>>>(dd);
}

#endif // TAUGAMMA_H
