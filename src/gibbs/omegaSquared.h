#ifndef OMEGASQUARED_H
#define OMEGASQUARED_H

__global__ void omegaSquared_kernel1(chain_t *dd){
  int n = IDX;
  if(n < dd->N)
    dd->aux[n] = dd->rho[n]*dd->rho[n];
}

__global__ void omegaSquared_kernel2(chain_t *dd){
  args_t args;
  args.idx = 0;
  args.x0 = dd->omegaSquared[0];
  args.target_type = LTARGET_INV_GAMMA;
  args.step_width = STEP_WIDTH;
  args.max_steps = MAX_STEPS;
  args.shape = 0.5 * ((double) dd->N - 1.0);
  args.scale = 0.5 * dd->aux[0];
  args.upperbound = dd->w[0] * dd->w[0];
  dd->omegaSquared[0] = slice(dd, args);
}

void omegaSquaredSample(SEXP hh, chain_t *hd, chain_t *dd){
  if(!(vi(le(hh, "parameter_sets_update"), "omegaSquared"))) return;

  omegaSquared_kernel1<<<GRID_N, BLOCK_N>>>(dd);

  thrust::device_ptr<double> tmp(hd->aux);
  double sum = thrust::reduce(tmp, tmp + li(hh, "N")[0]);
  CUDA_CALL(cudaMemcpy(hd->aux, &sum, sizeof(double), cudaMemcpyHostToDevice));

  omegaSquared_kernel2<<<1, 1>>>(dd);
}

#endif // OMEGASQUARED_H
