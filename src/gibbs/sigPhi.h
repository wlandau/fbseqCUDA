#ifndef SIGPHI_H
#define SIGPHI_H

__global__ void sigPhi_kernel1(chain_t *dd){
  int g = IDX;
  double x;
  if(g < dd->G){
    x = dd->phi[g] - dd->thePhi[0];
    dd->aux[g] = x * x / dd->xiPhi[g];
  }
}

__global__ void sigPhi_kernel2(chain_t *dd){
  approx_gibbs_args_t args;
  args.idx = 0;
  args.x0 = dd->sigPhi[0] * dd->sigPhi[0];
  args.target_type = LTARGET_INV_GAMMA;
  args.step_width = STEP_WIDTH;
  args.max_steps = MAX_STEPS;
  args.shape = 0.5 * ((double) dd->G - 1.0);
  args.scale = 0.5 * dd->aux[0];
  args.upperbound = dd->sPhi[0] * dd->sPhi[0];
  dd->sigPhi[0] = sqrt(stepping_out_slice(dd, args));
}

void sigPhiSample(SEXP hh, chain_t *hd, chain_t *dd){
  if(!(vi(le(hh, "updates"), "sigPhi"))) return;

  sigPhi_kernel1<<<GRID, BLOCK>>>(dd);

  thrust::device_ptr<double> tmp(hd->aux);
  double sum = thrust::reduce(tmp, tmp + li(hh, "G")[0]);
  CUDA_CALL(cudaMemcpy(hd->aux, &sum, sizeof(double), cudaMemcpyHostToDevice)); // hd->aux[0] = sum of the (phi_g - theta_phi)^2's

  sigPhi_kernel2<<<1, 1>>>(dd);
}

#endif // SIGPHI_H
