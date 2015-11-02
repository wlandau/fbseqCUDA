#ifndef PI_H
#define PI_H

__global__ void pi_kernel1(chain_t *dd, double aux, int l){ // single thread
  dd->pi[l] = rbeta(dd, l, 1.0 + aux, dd->G + 1.0 - aux);
}

void piSample(SEXP hh, chain_t *hd, chain_t *dd){
  int l, G = li(hh, "G")[0];
  if(!(vi(le(hh, "parameter_sets_update"), "pi"))) return;

  for(l = 0; l < li(hh, "L")[0]; ++l){
    thrust::device_ptr<double> tmp(hd->delta + l*G);
    double aux = thrust::reduce(tmp, tmp + G);
    pi_kernel1<<<1, 1>>>(dd, aux, l);
  }
}

#endif // PI_H
