#ifndef BETA_H
#define BETA_H

__device__ double beta_coef(chain_t *dd, int l, int g, double x){
  int i, n;
  double aux, out = 0.0, tol = 1e-9;
  for(n = 0; n < dd->N; ++n)
    if(fabs(dd->design[Idesign(l, n)] - x) < tol){
      aux = dd->h[n] + dd->epsilon[I(n, g)];
      for(i = 0; i < dd->L; ++i)
        if(i != l)
          aux += dd->design[Idesign(i, n)] * dd->beta[I(i, g)];
      out += exp(aux);
    }
  return out;
}

__global__ void beta_kernel1(chain_t *dd, int l){
  int g = IDX, j, n;

  if(g >= dd->G)
    return;

  args_t args;
  args.idx = g;
  args.x0 = dd->beta[I(l, g)];
  args.target_type = LTARGET_BETA;
  args.step_width = STEP_WIDTH;
  args.max_steps = MAX_STEPS;

  args.A = 0.0;
  for(n = 0; n < dd->N; ++n)
    args.A += ((double) dd->counts[I(n, g)])
            * ((double) dd->design[Idesign(l, n)]);

  args.B = 1.0/(2.0 * dd->sigmaSquared[l] * dd->xi[I(l, g)]);
  args.C = dd->theta[l];

  args.designUniqueN = dd->designUniqueN[l];

  for(j = 0; j < args.designUniqueN; ++j){
    dd->D[I(j, g)] = dd->designUnique[Idesign(l, j)];
    dd->aux[I(j, g)] = beta_coef(dd, l, g, dd->D[I(j, g)]);
  }

  dd->beta[I(l, g)] = slice(dd, args);
}

void betaSample(SEXP hh, chain_t *hd, chain_t *dd){
  int i, l;
  if(!(vi(le(hh, "parameter_sets_update"), "beta"))) return;
  for(i = 0; i < li(hh, "Lupdate_beta")[0]; ++i){
    l = li(hh, "effects_update_beta")[i] - 1;
    beta_kernel1<<<GRID, BLOCK>>>(dd, l);
  }
}

#endif // BETA_H
