#ifndef UTIL_LOGLIK_H
#define UTIL_LOGLIK_H

__global__ void loglik_kernel1(chain_t *dd){
  int n, g;
  double lambda;

  for(n = IDY; n < dd->N; n += NTHREADSY){
    for(g = IDX; g < dd->G; g += NTHREADSX){
      lambda = dd->h[n] + dd->epsilon[I(n, g)] + Xbeta(dd, n, g);
      dd->aux[I(n, g)] = -lambda + dd->y[I(n, g)] * log(lambda);
    }
  }
}

__global__ void loglik_kernel2(chain_t *dd){
  dd->loglik[0] = ll;
}

void nuSample(SEXP hh, chain_t *hd, chain_t *dd){
  int N = li(hh, "N")[0], G = li(hh, "G")[0];
  dim3 grid(GRID_G, GRID_N), block(BLOCK_G, BLOCK_N);
  loglik_kernel1<<<grid, block>>>(dd);
  thrust::device_ptr<double> tmp(hd->aux);
  double ll = thrust::reduce(tmp, tmp + N*G);
  loglik_kernel2<<<1, 1>>>(dd, ll);
}

#endif // UTIL_LOGLIK_H
