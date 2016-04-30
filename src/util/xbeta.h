#ifndef UTIL_XBETA_H
#define UTIL_XBETA_H

double Xbeta(chain_t *dd, int n, int g){
  int l;
  double out = 0.0;
  for(l = 0; l < dd->L; ++l)
    out += dd->design[Idesign(l, n)] * dd->beta[I(l, g)];
  return out;
}

#endif // UTIL_XBETA_H
