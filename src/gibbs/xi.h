#ifndef GIBBS_XI_H
#define GIBBS_XI_H

__global__ void xi_kernel1(chain_t *dd, int prior, int l){
  int g = IDX;
  if(g >= dd->G) return;

  args_t args;
  args.idx = g;
  args.m = dd->m;
  args.sumDiff = dd->xiSumDiff[I(l, g)];
  args.width = dd->xiWidth[I(l, g)];
  args.x0 = dd->xi[I(l, g)];

  double z = dd->beta[I(l, g)] - dd->theta[l];
  z = 0.5 * z * z / dd->sigmaSquared[l];

  switch(prior){
    case PRIOR_LAPLACE:
      args.target_type = LTARGET_XI_LAPLACE;
      args.A = z;
      args.B = dd->k[l];
      break;

    case PRIOR_T:
      args.target_type = LTARGET_XI_T;
      args.A = dd->q[l] + 1.5;
      args.B = z + dd->r[l];
      break;

    case PRIOR_HORSESHOE:
      args.target_type = LTARGET_XI_HORSESHOE;
      args.A = z;
      break;

    default:
      dd->xi[I(l, g)] = 1.0;
      return;
  }

  args = slice(dd, args);
  dd->xi[I(l, g)] = args.x;
  dd->xiSumDiff[I(l, g)] = args.sumDiff;
  dd->xiWidth[I(l, g)] = args.width;
}

void xiSample(SEXP hh, chain_t *hd, chain_t *dd){
  int l;
  if(!(vi(le(hh, "parameter_sets_update"), "xi"))) return;
  for(l = 0; l < li(hh, "L")[0]; ++l)
    xi_kernel1<<<GRID, BLOCK>>>(dd, li(hh, "priors")[l], l);
}

#endif // GIBBS_XI_H
