#ifndef GIBBS_XI_H
#define GIBBS_XI_H

void xi_kernel1(chain_t *dd, int prior, int l, int sampler){
  int g;
  for(g = IDX; g < dd->G; g += NTHREADSX){

    args_t args;
    args.idx = g;
    args.lowerbound = 0.0;
    args.m = dd->m;
    args.sampler = sampler;
    args.tuneAux = dd->xiTuneAux[I(l, g)];
    args.tune = dd->xiTune[I(l, g)];
    args.upperbound = INFINITY;
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

    args = sampler_wrap(dd, args);
    dd->xi[I(l, g)] = args.x;
    dd->xiTune[I(l, g)] = args.tune;
    dd->xiTuneAux[I(l, g)] = args.tuneAux;
  }
}

void xiSample(SEXP hh, chain_t *hd, chain_t *dd){
  int l;
  if(!(vi(le(hh, "parameter_sets_update"), "xi"))) return;
  for(l = 0; l < li(hh, "L")[0]; ++l)
    xi_kernel1(dd, li(hh, "priors")[l], l, li(hh, "xiSampler")[0]);
}

#endif // GIBBS_XI_H
