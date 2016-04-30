#ifndef UTIL_CUDA_USAGE_H
#define UTIL_CUDA_USAGE_H

#define IDX 0
#define IDY 0
#define NTHREADSX 1
#define NTHREADSY 1

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

void serial_reduce_aux(chain_t *dd){
  int g;
  for(g = 1; g < dd->G; ++g)
    dd->aux[0] = dd->aux[0] + dd->aux[g];
}

#endif // UTIL_CUDA_USAGE_H
