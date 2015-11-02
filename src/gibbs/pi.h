#ifndef PI_H
#define PI_H

__global__ void pi_kernel1(chain_t *dd, int aux, int l){ // single thread
  if(!dd->p[l]){
    dd->pi[l] = 1;
    return;
  }

  args_t args;
  args.idx = l;
  args.x0 = dd->pi[l];
  args.target_type = LTARGET_BETA_DIST;
  args.step_width = STEP_WIDTH;
  args.max_steps = MAX_STEPS;
  args.shape1 = 1.0 + aux;
  args.shape2 = dd->G + 1.0 - aux;
  dd->pi[l] = slice(dd, args);
}

void piSample(SEXP hh, chain_t *hd, chain_t *dd){
  int l, G = li(hh, "G")[0];
  if(!(vi(le(hh, "parameter_sets_update"), "pi"))) return;

  for(l = 0; l < li(hh, "L")[0]; ++l){
    thrust::device_ptr<int> tmp(hd->delta + l*G);
    int aux = thrust::reduce(tmp, tmp + G);
    pi_kernel1<<<1, 1>>>(dd, aux, l);
  }
}

#endif // PI_H
