#ifndef XI_H
#define XI_H

__global__ void xi_kernel1(chain_t *dd, int l){
  int g = IDX, prior = li(hh, "priors")[l];
  if(g >= dd->G) return;

  approx_gibbs_args_t args;
  args.idx = g;
  args.x0 = dd->xi[I(l, g)];
  args.step_width = STEP_WIDTH;
  args.max_steps = MAX_STEPS;

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
      args.A = dd->k[l] + 1.5;
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

  dd->xi[I(l, g)] = slice(dd, args);
}

void xiSample(SEXP hh, chain_t *hd, chain_t *dd){
  int l;
  if(!(vi(le(hh, "updates"), "xi"))) return;
  for(l = 0; l < li(hh, "L")[0]; ++l)
    xi_kernel1<<<GRID, BLOCK>>>(dd, l);
}

#endif // XI_H
