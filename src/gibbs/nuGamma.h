#ifndef NUGAMMA_H
#define NUGAMMA_H

__global__ void nuGamma_kernel1(chain_t *dd){
  int g = IDX;
  if(g < dd->G)
    dd->aux[g] = log(dd->gamma[g]) + 0.5 * dd->tauGamma[0] / dd->gamma[g];
}

__global__ void nuGamma_kernel2(chain_t *dd){
  approx_gibbs_args_t args;
  args.idx = 0;
  args.x0 = dd->nuGamma[0];
  args.target_type = LTARGET_NU;
  args.step_width = STEP_WIDTH;
  args.max_steps = MAX_STEPS;

  args.A = 0.5 * dd->tauGamma[0];
  args.B = dd->aux[0];
  args.C = (double) dd->G;
  args.D = dd->dGamma[0];

  dd->nuGamma[0] = slice(dd, args);
}

void nuGammaSample(SEXP hh, chain_t *hd, chain_t *dd){
  if(!(vi(le(hh, "updates"), "nuGamma"))) return;
  nuGamma_kernel1<<<GRID, BLOCK>>>(dd);

  thrust::device_ptr<double> aux(hd->aux);
  double sum = thrust::reduce(aux, aux + li(hh, "G")[0]);
  CUDA_CALL(cudaMemcpy(hd->aux, &sum, sizeof(double), cudaMemcpyHostToDevice));

  nuGamma_kernel2<<<1, 1>>>(dd);
}

#endif // NUGAMMA_H
