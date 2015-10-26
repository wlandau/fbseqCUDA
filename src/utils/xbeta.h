#ifndef XBETA_H
#define XBETA_H

__device__ double Xbeta(chain_t *dd, int n, int g){
  return Y(n, g);
}

#endif // XBETA_H
