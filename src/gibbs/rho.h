#ifndef RHO_H
#define RHO_H

__global__ void rho_kernel1(chain_t *dd, int n){
  int g = IDX;
  if(g < dd->G)
    dd->aux[g] = 1.0 / dd->gamma[g];
}

__global__ void rho_kernel2(chain_t *dd, int n){
  int g = IDX;
  if(g < dd->G)
    dd->aux[g] = dd->epsilon[I(n, g)] / dd->gamma[g];
}

__global__ void rho_kernel3(chain_t *dd, double A0, double B0, int n){ // single thread
  double A = 0.5 * (1.0/(dd->w[0]*dd->w[0]) + A0/dd->omegaSquared[0]),
         B = B0/dd->omegaSquared[0];
  dd->rho[n] = rnormal(dd, 0, 0.5*B/A, sqrt(0.5/A));
}

void rhoSample(SEXP hh, chain_t *hd, chain_t *dd){
  int n, G = li(hh, "G")[0];
  if(!(vi(le(hh, "parameter_sets_update"), "rho"))) return;

  for(n = 0; n < li(hh, "N")[0]; ++n){
    rho_kernel1<<<GRID, BLOCK>>>(dd, n);
    thrust::device_ptr<double> tmpA(hd->aux);
    double A0 = thrust::reduce(tmpA, tmpA + G);

    rho_kernel2<<<GRID, BLOCK>>>(dd, n);
    thrust::device_ptr<double> tmpB(hd->aux);
    double B0 = thrust::reduce(tmpB, tmpB + G);

    rho_kernel3<<<1, 1>>>(dd, A0, B0, n);
  }
}

#endif // RHO_H
