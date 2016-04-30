#ifndef GIBBS_SIGMASQUARED_H
#define GIBBS_SIGMASQUARED_H

void sigmaSquared_kernel1(chain_t *dd, int l){
  int g;
  double x;
  for(g = IDX; g < dd->G; g += NTHREADSX){
    x = dd->beta[I(l, g)] - dd->theta[l];
    dd->aux[g] = x * x / dd->xi[I(l, g)];
  }
}

void sigmaSquared_kernel2(chain_t *dd, int l, int sampler){
  args_t args;
  args.idx = 0;
  args.lowerbound = 0.0;
  args.m = dd->m;
  args.sampler = sampler;
  args.tuneAux = dd->sigmaSquaredTuneAux[l];
  args.target_type = LTARGET_INV_GAMMA;
  args.tune = dd->sigmaSquaredTune[l];
  args.upperbound = dd->s[l] * dd->s[l];
  args.x0 = dd->sigmaSquared[l];

  args.shape = 0.5 * ((double) dd->G - 1.0);
  args.scale = 0.5 * dd->aux[0];

  args = sampler_wrap(dd, args);
  dd->sigmaSquared[l] = args.x;
  dd->sigmaSquaredTune[l] = args.tune;
  dd->sigmaSquaredTuneAux[l] = args.tuneAux;
}

void sigmaSquaredSample(SEXP hh, chain_t *hd, chain_t *dd){
  int l;
  if(!(vi(le(hh, "parameter_sets_update"), "sigmaSquared"))) return;

  for(l = 0; l < li(hh, "L")[0]; ++l){
    sigmaSquared_kernel1(dd, l);

//    thrust::device_ptr<double> tmp(hd->aux);
//    double sum = thrust::reduce(tmp, tmp + li(hh, "G")[0]);
//    CUDA_CALL(cudaMemcpy(hd->aux, &sum, sizeof(double), cudaMemcpyHostToDevice));
    serial_reduce_aux(dd);

    sigmaSquared_kernel2(dd, l, li(hh, "sigmaSquaredSampler")[0]);
  }
}

#endif // GIBBS_SIGMASQUARED_H
