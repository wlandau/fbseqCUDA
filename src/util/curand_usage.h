#ifndef UTIL_CURAND_USAGE_H
#define UTIL_CURAND_USAGE_H

__global__ void curand_setup_kernel(chain_t *dd){
  int n = IDX, g = IDY, id = I(n, g);
  if(n < dd->N && g < dd->G)
    curand_init(dd->seeds[id], id, id % dd->G, dd->states + id);
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

#endif // UTIL_CURAND_USAGE_H
