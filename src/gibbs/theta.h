#ifndef THETA_H
#define THETA_H

__global__ void theta_kernel1(chain_t *dd){
  int g = IDX;
  if(g < dd->G)
    dd->aux[g] = dd->phi[g] / dd->xi[g];
}

__global__ void theta_kernel2(chain_t *dd){
  int g = IDX;
  if(g < dd->G)
    dd->aux[g] = 1.0 / dd->xi[g];
}

__global__ void theta_kernel3(chain_t *dd, double numsum, double densum){ // single thread
  double cPhiSq = pow(*(dd->cPhi), 2),
        sigPhiSq = pow(*(dd->sigPhi), 2),

        denom = cPhiSq * densum + sigPhiSq,
        mean = cPhiSq * numsum / denom,
        sd = sqrt(cPhiSq * sigPhiSq / denom);

  dd->theta[0] = rnormal(dd, 0, mean, sd);
}

void thetaSample(SEXP hh, chain_t *hd, chain_t *dd){
  int G = li(hh, "G")[0];
  if(!(vi(le(hh, "updates"), "theta"))) return;

  theta_kernel1<<<GRID, BLOCK>>>(dd);
  thrust::device_ptr<double> tmp1(hd->aux);
  double numsum = thrust::reduce(tmp1, tmp1 + G);

  theta_kernel2<<<GRID, BLOCK>>>(dd);
  thrust::device_ptr<double> tmp2(hd->aux);
  double densum = thrust::reduce(tmp2, tmp2 + G);

  theta_kernel3<<<1, 1>>>(dd, numsum, densum);
}

#endif // THETA_H
