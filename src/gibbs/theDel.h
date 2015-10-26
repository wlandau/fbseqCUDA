#ifndef THEDEL_H
#define THEDEL_H

__global__ void theDel_kernel1(chain_t *dd){
  int g = IDX;
  if(g < dd->G)
    dd->aux[g] = dd->del[g] / dd->xiDel[g];
}

__global__ void theDel_kernel2(chain_t *dd){
  int g = IDX;
  if(g < dd->G)
    dd->aux[g] = 1.0 / dd->xiDel[g];
}

__global__ void theDel_kernel3(chain_t *dd, double numsum, double densum){ // single thread
  double cDelSq = pow(*(dd->cDel), 2),
        sigDelSq = pow(*(dd->sigDel), 2),

        denom = cDelSq * densum + sigDelSq,
        mean = cDelSq * numsum / denom,
        sd = sqrt(cDelSq * sigDelSq / denom);

  dd->theDel[0] = rnormal(dd, 0, mean, sd);
}

void theDelSample(SEXP hh, chain_t *hd, chain_t *dd){
  int G = li(hh, "G")[0];
  if(!(vi(le(hh, "updates"), "theDel"))) return;

  theDel_kernel1<<<GRID, BLOCK>>>(dd);
  thrust::device_ptr<double> tmp1(hd->aux);
  double numsum = thrust::reduce(tmp1, tmp1 + G);

  theDel_kernel2<<<GRID, BLOCK>>>(dd);
  thrust::device_ptr<double> tmp2(hd->aux);
  double densum = thrust::reduce(tmp2, tmp2 + G);

  theDel_kernel3<<<1, 1>>>(dd, numsum, densum);
}

#endif // THEDEL_H
