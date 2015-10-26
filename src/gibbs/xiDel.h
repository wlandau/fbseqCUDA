#ifndef XIDEL_H
#define XIDEL_H

__global__ void xiDel_kernel1(chain_t *dd, int prior){
  int g = IDX;
  if(g >= dd->G) return;

  approx_gibbs_args_t args;
  args.idx = g;
  args.x0 = dd->xiDel[g];
  args.step_width = STEP_WIDTH;
  args.max_steps = MAX_STEPS;

  double z = dd->del[g] - dd->theDel[0];
  z = (z*z)/(2.0 * dd->sigDel[0] * dd->sigDel[0]);

  switch(prior){
    case PRIOR_LAPLACE:
      args.target_type = LTARGET_XI_LAPLACE;
      args.A = z;
      args.B = dd->kDel[0];
      break;

    case PRIOR_T:
      args.target_type = LTARGET_XI_T;
      args.A = dd->kDel[0] + 1.5;
      args.B = z + dd->rDel[0];
      break;

    case PRIOR_HORSESHOE:
      args.target_type = LTARGET_XI_HORSESHOE;
      args.A = z;
      break;

    default:
      return;
  }

  dd->xiDel[g] = stepping_out_slice(dd, args);
}

void xiDelSample(SEXP hh, chain_t *hd, chain_t *dd){
  if(!(vi(le(hh, "updates"), "xiDel"))) return;
  xiDel_kernel1<<<GRID, BLOCK>>>(dd, li(hh, "delPrior")[0]);
}

#endif // XIDEL_H
