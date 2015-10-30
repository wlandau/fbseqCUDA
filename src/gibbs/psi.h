#ifndef PSI_H
#define PSI_H

__global__ void psi_kernel1(chain_t *dd, int n){
  int g = IDX;
  if(g < dd->G)
    dd->aux[g] = 1.0 / dd->gamma[g];
}

__global__ void psi_kernel2(chain_t *dd, int n){
  int g = IDX;
  if(g < dd->G)
    dd->aux[g] = dd->epsilon[I(n, g)] / dd->gamma[g];
}

__global__ void psi_kernel3(chain_t *dd, double A0, double B0, int n){ // single thread
  double A = 0.5 * (1.0/dd->omegaSquared[0] + A0/dd->rho[n]),
         B = B0/dd->rho[n];
  dd->psi[n] = rnormal(dd, 0, 0.5*B/A, sqrt(0.5/A));
}

void psiSample(SEXP hh, chain_t *hd, chain_t *dd){
  int n, G = li(hh, "G")[0];
  if(!(vi(le(hh, "parameter_sets_update"), "psi"))) return;

  for(n = 0; n < li(hh, "N")[0]; ++n){
    psi_kernel1<<<GRID, BLOCK>>>(dd, n);
    thrust::device_ptr<double> tmpA(hd->aux);
    double A0 = thrust::reduce(tmpA, tmpA + G);

    psi_kernel2<<<GRID, BLOCK>>>(dd, n);
    thrust::device_ptr<double> tmpB(hd->aux);
    double B0 = thrust::reduce(tmpB, tmpB + G);

    psi_kernel3<<<1, 1>>>(dd, A0, B0, n);
  }
}

#endif // PSI_H
