#ifndef ETA_H
#define ETA_H

__device__ double eta(chain_t *dd, int n, int g){
  if(dd->group[n] == 1)
    return dd->phi[g] + dd->alp[g] - dd->del[g];
  else if(dd->group[n] == 2)
    return dd->phi[g] - dd->alp[g] + dd->del[g];
  else
    return dd->phi[g] + dd->alp[g] + dd->del[g];
}

#endif // ETA_H
