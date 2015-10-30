#ifndef RHO_H
#define RHO_H

__global__ void rho_kernel1(chain_t *dd, int n){
  int g = IDX;
  double z;
  if(g >= dd->G) return;
  z = dd->epsilon[I(n, g)] - dd->h[n];
  dd->aux[g] = z * z / dd->gamma[g];
}

__global__ void rho_kernel2(chain_t *dd, int n, double sum){ // single thread
  args_t args;
  args.x0 = dd->rho[n];
  args.target_type = LTARGET_INV_GAMMA;
  args.step_width = STEP_WIDTH;
  args.max_steps = MAX_STEPS;
  args.shape = 0.5 * (dd->G + dd->nuRho[0]);
  args.scale = 0.5 * (dd->nuRho[0] * dd->tauRho[0] + sum);
  args.upperbound = CUDART_INF;
  dd->rho[n] = slice(dd, args);
}

void rhoSample(SEXP hh, chain_t *hd, chain_t *dd){
  int n, N = li(hh, "N")[0], G = li(hh, "G")[0];
  if(!(vi(le(hh, "parameter_sets_update"), "rho"))) return;

  for(n = 0; n < N; ++n){
    rho_kernel1<<<GRID, BLOCK>>>(dd, n);
    thrust::device_ptr<double> tmp(hd->aux);
    double sum = thrust::reduce(tmp, tmp + G);
    rho_kernel2<<<1, 1>>>(dd, n, sum);
  }
}

#endif // RHO_H
