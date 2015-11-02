#ifndef DELTA_H
#define DELTA_H

__global__ void delta_kernel1(chain_t *dd, int l){
  int g = IDX;
  double x, y, z, logit_p, logit_u;

  if(g >= dd->G)
    return;

  if(!dd->p[l]){
    dd->delta[I(l, g)] = 1;
    return;
  }

  x = dd->beta[I(l, g)];
  y = x - dd->theta[l];
  z = 0.5 * (y*y - x*x)/(dd->sigmaSquared[l] * dd->xi[I(l, g)]);
  logit_p = -log(1.0/dd->pi[l] - 1.0) - z;
  logit_u = -log(1.0/runiform(dd, l, 0.0, 1.0) - 1.0);
  dd->delta[I(l, g)] = logit_u < logit_p;
}

void deltaSample(SEXP hh, chain_t *hd, chain_t *dd){
  int l;
  if(!(vi(le(hh, "parameter_sets_update"), "delta"))) return;
  for(l = 0; l < li(hh, "L")[0]; ++l)
    delta_kernel1<<<GRID, BLOCK>>>(dd, l);
}

#endif // DELTA_H
