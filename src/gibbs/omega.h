#ifndef SIGMASQUARED_H
#define SIGMASQUARED_H

__global__ void sigmaSquared_kernel1(chain_t *dd, l){
  int g = IDX;
  double x;
  if(g < dd->G){
    x = dd->beta[I(l, g)] - dd->theta[l];
    dd->aux[g] = x * x / dd->xi[I(l, g)];
  }
}

__global__ void sigmaSquared_kernel2(chain_t *dd, l){
  approx_gibbs_args_t args;
  args.idx = 0;
  args.x0 = dd->sigmaSquared[l];
  args.target_type = LTARGET_INV_GAMMA;
  args.step_width = STEP_WIDTH;
  args.max_steps = MAX_STEPS;
  args.shape = 0.5 * ((double) dd->G - 1.0);
  args.scale = 0.5 * dd->aux[0];
  args.upperbound = dd->s[l] * dd->s[l];
  dd->sigmaSquared[l] = slice(dd, args);
}

void sigmaSquaredSample(SEXP hh, chain_t *hd, chain_t *dd){
  int l;
  if(!(vi(le(hh, "updates"), "sigmaSquared"))) return;

  for(l = 0; l < li(hh, "L")[0]; ++l){
    sigmaSquared_kernel1<<<GRID, BLOCK>>>(dd, l);

    thrust::device_ptr<double> tmp(hd->aux);
    double sum = thrust::reduce(tmp, tmp + li(hh, "G")[0]);
    CUDA_CALL(cudaMemcpy(hd->aux, &sum, sizeof(double), cudaMemcpyHostToDevice));

    sigmaSquared_kernel2<<<1, 1>>>(dd, l);
  }
}

#endif // SIGMASQUARED_H
