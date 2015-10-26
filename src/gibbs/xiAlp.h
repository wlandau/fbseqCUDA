#ifndef XIALP_H
#define XIALP_H

__global__ void xiAlp_kernel1(chain_t *dd, int prior){
  int g = IDX;
  if(g >= dd->G) return;

  approx_gibbs_args_t args;
  args.idx = g;
  args.x0 = dd->xiAlp[g];
  args.step_width = STEP_WIDTH;
  args.max_steps = MAX_STEPS;

  double z = dd->alp[g] - dd->theAlp[0];
  z = (z*z)/(2.0 * dd->sigAlp[0] * dd->sigAlp[0]);

  switch(prior){
    case PRIOR_LAPLACE:
      args.target_type = LTARGET_XI_LAPLACE;
      args.A = z;
      args.B = dd->kAlp[0];
      break;

    case PRIOR_T:
      args.target_type = LTARGET_XI_T;
      args.A = dd->kAlp[0] + 1.5;
      args.B = z + dd->rAlp[0];
      break;

    case PRIOR_HORSESHOE:
      args.target_type = LTARGET_XI_HORSESHOE;
      args.A = z;
      break;

    default:
      return;
  }

  dd->xiAlp[g] = stepping_out_slice(dd, args);
}

void xiAlpSample(SEXP hh, chain_t *hd, chain_t *dd){
  if(!(vi(le(hh, "updates"), "xiAlp"))) return;
  xiAlp_kernel1<<<GRID, BLOCK>>>(dd, li(hh, "alpPrior")[0]);
}

#endif // XIALP_H
