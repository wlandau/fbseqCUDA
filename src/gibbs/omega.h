#ifndef OMEGA_H
#define OMEGA_H

__global__ void omega_kernel1(chain_t *dd){
  int g = IDX;
  double x;
  if(g < dd->G){
    x = dd->alp[g] - dd->theAlp[0];
    dd->aux[g] = x * x / dd->xiAlp[g];
  }
}

__global__ void omega_kernel2(chain_t *dd){
  approx_gibbs_args_t args;
  args.idx = 0;
  args.x0 = dd->omega[0] * dd->omega[0];
  args.target_type = LTARGET_INV_GAMMA;
  args.step_width = STEP_WIDTH;
  args.max_steps = MAX_STEPS;
  args.shape = 0.5 * ((double) dd->G - 1.0);
  args.scale = 0.5 * dd->aux[0];
  args.upperbound = dd->sAlp[0] * dd->sAlp[0];
  dd->omega[0] = slice(dd, args);
}

void omegaSample(SEXP hh, chain_t *hd, chain_t *dd){
  if(!(vi(le(hh, "updates"), "omega"))) return;

  omega_kernel1<<<GRID, BLOCK>>>(dd);

  thrust::device_ptr<double> tmp(hd->aux);
  double sum = thrust::reduce(tmp, tmp + li(hh, "G")[0]);
  CUDA_CALL(cudaMemcpy(hd->aux, &sum, sizeof(double), cudaMemcpyHostToDevice)); // hd->aux[0] = sum of the (Alp_g - theta_Alp)^2's

  omega_kernel2<<<1, 1>>>(dd);
}

#endif // OMEGA_H
