#ifndef GIBBS_THETA_H
#define GIBBS_THETA_H

__global__ void theta_kernel1(chain_t *dd, int l){
  int g;
  for(g = IDX; g < dd->G; g += NTHREADSX)
    dd->aux[g] = 1.0 / dd->xi[I(l, g)];
}

__global__ void theta_kernel2(chain_t *dd, int l){
  int g;
  for(g = IDX; g < dd->G; g += NTHREADSX)
    dd->aux[g] = dd->beta[I(l, g)] / dd->xi[I(l, g)];
}

__global__ void theta_kernel3(chain_t *dd, double A0, double B0, int l){ // single thread
  double A = 0.5 * (1.0/(dd->c[l]*dd->c[l]) + A0/dd->sigmaSquared[l]),
         B = B0/dd->sigmaSquared[l];
  dd->theta[l] = rnormal(dd, l, 0.5*B/A, sqrt(0.5/A));
}

void thetaSample(SEXP hh, chain_t *hd, chain_t *dd){
  int l, G = li(hh, "G")[0];
  if(!(vi(le(hh, "parameter_sets_update"), "theta"))) return;

  for(i = 0; i < li(hh, "Lupdate_theta")[0]; ++i){
    l = li(hh, "theta_update")[i] - 1;

    theta_kernel1<<<GRID, BLOCK>>>(dd, l);
    thrust::device_ptr<double> tmpA(hd->aux);
    double A0 = thrust::reduce(tmpA, tmpA + G);

    theta_kernel2<<<GRID, BLOCK>>>(dd, l);
    thrust::device_ptr<double> tmpB(hd->aux);
    double B0 = thrust::reduce(tmpB, tmpB + G);

    theta_kernel3<<<1, 1>>>(dd, A0, B0, l);
  }
}

#endif // GIBBS_THETA_H
