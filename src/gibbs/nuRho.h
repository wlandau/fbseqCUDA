#ifndef NURHO_H
#define NURHO_H

__global__ void nuRho_kernel1(chain_t *dd){
  int n = IDX;
  if(n < dd->N)
    dd->aux[n] = log(dd->rho[n]) + 0.5 * (dd->tauRho[0] * dd->tauRho[0]) / (dd->rho[n] * dd->rho[n]);
}

__global__ void nuRho_kernel2(chain_t *dd){
  approx_gibbs_args_t args;
  args.idx = 0;
  args.x0 = dd->nuRho[0];
  args.target_type = LTARGET_NU;
  args.step_width = STEP_WIDTH;
  args.max_steps = MAX_STEPS;

  args.A = 0.5 * dd->tauRho[0]*dd->tauRho[0];
  args.B = dd->aux[0] / ((double) dd->N);
  args.C = (double) dd->N;
  args.D = dd->dRho[0];

  dd->nuRho[0] = stepping_out_slice(dd, args);
}

void nuRhoSample(SEXP hh, chain_t *hd, chain_t *dd){
  if(!(vi(le(hh, "updates"), "nuRho"))) return;
  nuRho_kernel1<<<GRID, BLOCK>>>(dd);

  thrust::device_ptr<double> aux(hd->aux);
  double sum = thrust::reduce(aux, aux + li(hh, "N")[0]);
  CUDA_CALL(cudaMemcpy(hd->aux, &sum, sizeof(double), cudaMemcpyHostToDevice));

  nuRho_kernel2<<<1, 1>>>(dd);
}

#endif // NURHO_H
