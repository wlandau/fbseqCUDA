#ifndef UTIL_SET_H
#define UTIL_SET_H

void set_adapt(chain_t *dd, int adapt){
  dd->adapt = adapt;
}

void set_m(chain_t *dd, int m){
  dd->m = m;
}

#endif // UTIL_SET_H
