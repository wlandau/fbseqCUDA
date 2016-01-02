#ifndef UTIL_CURAND_USAGE_H
#define UTIL_CURAND_USAGE_H

__global__ void curand_setup_kernel(chain_t *dd){
  int n, g, id;
  for(n = IDX; n < dd->N; n += NTHREADSX){
    for(g = IDY; g < dd->G; g += NTHREADSY){
      id = = I(n, g);
      curand_init(dd->seeds[id], id, id % dd->G, dd->states + id);
    }
  }
}

__device__ double runiform(chain_t *dd, int g, double LB, double UB){
  curandState_t localState = dd->states[g];
  double x = curand_uniform_double(&localState);
  dd->states[g] = localState;
  return x * (UB - LB) + LB;
}

__device__ double rnormal(chain_t *dd, int g, double mean, double sd){
  curandState_t localState = dd->states[g];
  double x = curand_normal_double(&localState);
  dd->states[g] = localState;
  return x * sd + mean;
}

__device__ double rt(chain_t *dd, int g, double mean, double scale, int df){
  double z = rnormal(dd, g, 0.0, 1.0), v = 0, x, t;
  int i;
  for(i = 0; i < df; ++i){
    x = rnormal(dd, g, 0.0, 1.0);
    v += x*x;
  }
  t = z/sqrt(v/df);
  return t*scale + mean;
}

#endif // UTIL_CURAND_USAGE_H
