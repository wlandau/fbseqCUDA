#ifndef THEPHI_H
#define THEPHI_H

__global__ void thePhi_kernel1(chain_t *dd){
  int g = IDX;
  if(g < dd->G)
    dd->aux[g] = dd->phi[g] / dd->xiPhi[g];
}

__global__ void thePhi_kernel2(chain_t *dd){
  int g = IDX;
  if(g < dd->G)
    dd->aux[g] = 1.0 / dd->xiPhi[g];
}

__global__ void thePhi_kernel3(chain_t *dd, double numsum, double densum){ // single thread
  double cPhiSq = pow(*(dd->cPhi), 2),
        sigPhiSq = pow(*(dd->sigPhi), 2),

        denom = cPhiSq * densum + sigPhiSq,
        mean = cPhiSq * numsum / denom,
        sd = sqrt(cPhiSq * sigPhiSq / denom);

  dd->thePhi[0] = rnormal(dd, 0, mean, sd);
}

void thePhiSample(SEXP hh, chain_t *hd, chain_t *dd){
  int G = li(hh, "G")[0];
  if(!(vi(le(hh, "updates"), "thePhi"))) return;

  thePhi_kernel1<<<GRID, BLOCK>>>(dd);
  thrust::device_ptr<double> tmp1(hd->aux);
  double numsum = thrust::reduce(tmp1, tmp1 + G);

  thePhi_kernel2<<<GRID, BLOCK>>>(dd);
  thrust::device_ptr<double> tmp2(hd->aux);
  double densum = thrust::reduce(tmp2, tmp2 + G);

  thePhi_kernel3<<<1, 1>>>(dd, numsum, densum);
}

#endif // THEPHI_H
