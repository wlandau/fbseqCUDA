#ifndef TAURHO_H
#define TAURHO_H

__global__ void tauRho_kernel1(chain_t *dd){
  int id = IDX;
  if(id < dd->N)
    dd->aux[id] = 1.0/(dd->rho[id] * dd->rho[id]);
}

__global__ void tauRho_kernel2(chain_t *dd){
  approx_gibbs_args_t args;
  args.idx = 0;
  args.x0 = dd->tauRho[0] * dd->tauRho[0];
  args.target_type = LTARGET_GAMMA;
  args.step_width = STEP_WIDTH;
  args.max_steps = MAX_STEPS;
  args.shape = dd->aRho[0] + dd->N * dd->nuRho[0] * 0.5;
  args.rate = dd->bRho[0] + dd->nuRho[0] * dd->aux[0] * 0.5;
  args.upperbound = CUDART_INF;
  dd->tauRho[0] = slice(dd, args);
}

void tauRhoSample(SEXP hh, chain_t *hd, chain_t *dd){
  if(!(vi(le(hh, "updates"), "tauRho"))) return;

  tauRho_kernel1<<<GRID, BLOCK>>>(dd);

  thrust::device_ptr<double> tmp(hd->aux);
  double sum = thrust::reduce(tmp, tmp + li(hh, "N")[0]);
  CUDA_CALL(cudaMemcpy(hd->aux, &sum, sizeof(double), cudaMemcpyHostToDevice));

  tauRho_kernel2<<<1, 1>>>(dd);
}

#endif // TAURHO_H
