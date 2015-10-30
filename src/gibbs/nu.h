#ifndef NU_H
#define NU_H

__global__ void nu_kernel1(chain_t *dd){
  int g = IDX;
  if(g < dd->G)
    dd->aux[g] = log(dd->gamma[g]) + dd->tau[0] / dd->gamma[g];
}

__global__ void nu_kernel2(chain_t *dd){
  args_t args;
  args.idx = 0;
  args.x0 = dd->nu[0];
  args.target_type = LTARGET_NU;
  args.step_width = STEP_WIDTH;
  args.max_steps = MAX_STEPS;

  args.A = 0.5 * dd->tau[0];
  args.B = 0.5 * dd->aux[0];
  args.C = (double) dd->G;
  args.D = dd->d[0];

  dd->nu[0] = slice(dd, args);
}

void nuSample(SEXP hh, chain_t *hd, chain_t *dd){
  if(!(vi(le(hh, "parameter_sets_update"), "nu"))) return;
  nu_kernel1<<<GRID, BLOCK>>>(dd);

  thrust::device_ptr<double> aux(hd->aux);
  double sum = thrust::reduce(aux, aux + li(hh, "G")[0]);
  CUDA_CALL(cudaMemcpy(hd->aux, &sum, sizeof(double), cudaMemcpyHostToDevice));

  nu_kernel2<<<1, 1>>>(dd);
}

#endif // NU_H
