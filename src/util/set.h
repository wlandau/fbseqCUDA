#ifndef UTIL_SET_H
#define UTIL_SET_H

__global__ void set_adapt(chain_t *dd, int adapt){
  dd->adapt = adapt;
}

__global__ void set_m(chain_t *dd, int m){
  dd->m = m;
}

__global__ void set_theta(chain_t *dd, int l, double x){
  dd->theta[l] = x;
}


#endif // UTIL_SET_H
