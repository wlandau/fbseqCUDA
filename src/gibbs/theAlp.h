#ifndef THEALP_H
#define THEALP_H

__global__ void theAlp_kernel1(chain_t *dd){
  int g = IDX;
  if(g < dd->G)
    dd->aux[g] = dd->alp[g] / dd->xiAlp[g];
}

__global__ void theAlp_kernel2(chain_t *dd){
  int g = IDX;
  if(g < dd->G)
    dd->aux[g] = 1.0 / dd->xiAlp[g];
}

__global__ void theAlp_kernel3(chain_t *dd, double numsum, double densum){ // single thread
  double cAlpSq = pow(*(dd->cAlp), 2),
        sigAlpSq = pow(*(dd->sigAlp), 2),

        denom = cAlpSq * densum + sigAlpSq,
        mean = cAlpSq * numsum / denom,
        sd = sqrt(cAlpSq * sigAlpSq / denom);

  dd->theAlp[0] = rnormal(dd, 0, mean, sd);
}

void theAlpSample(SEXP hh, chain_t *hd, chain_t *dd){
  int G = li(hh, "G")[0];
  if(!(vi(le(hh, "updates"), "theAlp"))) return;

  theAlp_kernel1<<<GRID, BLOCK>>>(dd);
  thrust::device_ptr<double> tmp1(hd->aux);
  double numsum = thrust::reduce(tmp1, tmp1 + G);

  theAlp_kernel2<<<GRID, BLOCK>>>(dd);
  thrust::device_ptr<double> tmp2(hd->aux);
  double densum = thrust::reduce(tmp2, tmp2 + G);

  theAlp_kernel3<<<1, 1>>>(dd, numsum, densum);
}

#endif // THEALP_H
