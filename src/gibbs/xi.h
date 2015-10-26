#ifndef XI_H
#define XI_H

__global__ void xi_kernel1(chain_t *dd, int prior){
  int g = IDX;
  if(g >= dd->G) return;

  approx_gibbs_args_t args;
  args.idx = g;
  args.x0 = dd->xi[g];
  args.step_width = STEP_WIDTH;
  args.max_steps = MAX_STEPS;

  double z = dd->phi[g] - dd->thePhi[0];
  z = (z*z)/(2.0 * dd->sigPhi[0] * dd->sigPhi[0]);

  switch(prior){
    case PRIOR_LAPLACE:
      args.target_type = LTARGET_XI_LAPLACE;
      args.A = z;
      args.B = dd->k[0];
      break;

    case PRIOR_T:
      args.target_type = LTARGET_XI_T;
      args.A = dd->k[0] + 1.5;
      args.B = z + dd->r[0];
      break;

    case PRIOR_HORSESHOE:
      args.target_type = LTARGET_XI_HORSESHOE;
      args.A = z;
      break;

    default:
      return;
  }

  dd->xi[g] = slice(dd, args);
}

void xiSample(SEXP hh, chain_t *hd, chain_t *dd){
  if(!(vi(le(hh, "updates"), "xi"))) return;
  xi_kernel1<<<GRID, BLOCK>>>(dd, li(hh, "phiPrior")[0]);
}

#endif // XI_H
