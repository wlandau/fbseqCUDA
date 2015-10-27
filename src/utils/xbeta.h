#ifndef XBETA_H
#define XBETA_H

__device__ double Xbeta(chain_t *dd, int n, int g){
  int l;
  double out = 0.0;
  for(l = 0; l < dd->L; ++l)
    out += dd->design[Idesign(l, n)] * dd->beta[I(n, g)];
  return out;
}

#endif // XBETA_H
