#ifndef SET_H
#define SET_H

__global__ void set_adapt(chain_t *dd, int adapt){
  dd->adapt = adapt;
}

__global__ void set_m(chain_t *dd, int m){
  dd->m = m;
}

#endif // SET_H
