#ifndef GIBBS_NU_H
#define GIBBS_NU_H

void nu_kernel1(chain_t *dd){
  int g;
  for(g = IDX; g < dd->G; g += NTHREADSX)
    dd->aux[g] = log(dd->gamma[g]) + dd->tau[0] / dd->gamma[g];
}

void nu_kernel2(chain_t *dd, int sampler){
  args_t args;
  args.idx = 0;
  args.lowerbound = 0.0;
  args.m = dd->m;
  args.sampler = sampler;
  args.tuneAux = dd->nuTuneAux[0];
  args.target_type = LTARGET_NU;
  args.tune = dd->nuTune[0];
  args.upperbound = INFINITY;
  args.x0 = dd->nu[0];

  args.A = 0.5 * dd->tau[0];
  args.B = 0.5 * dd->aux[0];
  args.C = (double) dd->G;
  args.D = dd->d[0];

  args = sampler_wrap(dd, args);
  dd->nu[0] = args.x;
  dd->nuTune[0] = args.tune;
  dd->nuTuneAux[0] = args.tuneAux;
}

void nuSample(SEXP hh, chain_t *hd, chain_t *dd){
  if(!(vi(le(hh, "parameter_sets_update"), "nu"))) return;
  nu_kernel1(dd);

//  thrust::device_ptr<double> aux(hd->aux);
//  double sum = thrust::reduce(aux, aux + li(hh, "G")[0]);
//  CUDA_CALL(cudaMemcpy(hd->aux, &sum, sizeof(double), cudaMemcpyHostToDevice));
  serial_reduce_aux(dd);

  nu_kernel2(dd, li(hh, "nuSampler")[0]);
}

#endif // GIBBS_NU_H
