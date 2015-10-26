#ifndef TAUGAM_H
#define TAUGAM_H

__global__ void tauGam_kernel1(chain_t *dd){
  int id = IDX;
  if(id < dd->G)
    dd->aux[id] = 1.0/(dd->gam[id] * dd->gam[id]);
}

__global__ void tauGam_kernel2(chain_t *dd){
  approx_gibbs_args_t args;
  args.idx = 0;
  args.x0 = dd->tauGam[0] * dd->tauGam[0];
  args.target_type = LTARGET_GAMMA;
  args.step_width = STEP_WIDTH;
  args.max_steps = MAX_STEPS;
  args.shape = dd->aGam[0] + dd->G * dd->nuGam[0] * 0.5;
  args.rate = dd->bGam[0] + dd->nuGam[0] * dd->aux[0] * 0.5;
  args.upperbound = CUDART_INF;
  dd->tauGam[0] = sqrt(stepping_out_slice(dd, args));
}

void tauGamSample(SEXP hh, chain_t *hd, chain_t *dd){
  if(!(vi(le(hh, "updates"), "tauGam"))) return;

  tauGam_kernel1<<<GRID, BLOCK>>>(dd);

  thrust::device_ptr<double> tmp(hd->aux);
  double sum = thrust::reduce(tmp, tmp + li(hh, "G")[0]);
  CUDA_CALL(cudaMemcpy(hd->aux, &sum, sizeof(double), cudaMemcpyHostToDevice)); // hd->aux[0] = sum of the 1/gam_g's

  tauGam_kernel2<<<1, 1>>>(dd);
}

#endif // TAUGAM_H
