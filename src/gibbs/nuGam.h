#ifndef NUGAM_H
#define NUGAM_H

__global__ void nuGam_kernel1(chain_t *dd){
  int g = IDX;
  if(g < dd->G)
    dd->aux[g] = log(dd->gam[g]) + 0.5 * (dd->tauGam[0] * dd->tauGam[0]) / (dd->gam[g] * dd->gam[g]);
}

__global__ void nuGam_kernel2(chain_t *dd){
  approx_gibbs_args_t args;
  args.idx = 0;
  args.x0 = dd->nuGam[0];
  args.target_type = LTARGET_NU;
  args.step_width = STEP_WIDTH;
  args.max_steps = MAX_STEPS;

  args.A = 0.5 * dd->tauGam[0]*dd->tauGam[0];
  args.B = dd->aux[0] / ((double) dd->G);
  args.C = (double) dd->G;
  args.D = dd->dGam[0];

  dd->nuGam[0] = stepping_out_slice(dd, args);
}

void nuGamSample(SEXP hh, chain_t *hd, chain_t *dd){
  if(!(vi(le(hh, "updates"), "nuGam"))) return;
  nuGam_kernel1<<<GRID, BLOCK>>>(dd);

  thrust::device_ptr<double> aux(hd->aux);
  double sum = thrust::reduce(aux, aux + li(hh, "G")[0]);
  CUDA_CALL(cudaMemcpy(hd->aux, &sum, sizeof(double), cudaMemcpyHostToDevice));

  nuGam_kernel2<<<1, 1>>>(dd);
}

#endif // NUGAM_H
