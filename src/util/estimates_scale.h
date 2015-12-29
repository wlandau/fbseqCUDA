#ifndef UTIL_ESTIMATES_SCALE_H
#define UTIL_ESTIMATES_SCALE_H

__global__ void estimates_scale_kernel1(chain_t *dd, double iterations){
  int l;

  dd->nuPostMean[0]/= iterations;
  dd->tauPostMean[0]/= iterations;

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredPostMean[l]/= iterations;
    dd->thetaPostMean[l]/= iterations;
  }
}

__global__ void estimates_scale_kernel2(chain_t *dd, double iterations){
  int l;
  dd->nuPostMeanSquare[0]/= iterations;
  dd->tauPostMeanSquare[0]/= iterations;

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredPostMeanSquare[l]/= iterations;
    dd->thetaPostMeanSquare[l]/= iterations;
  }
}

__global__ void estimates_scale_kernel3(chain_t *dd, double iterations){
  int id = IDX, l, n;
  if(id >= dd->G) return;

  dd->gammaPostMean[id]/= iterations;
  for(l = 0; l < dd->L; ++l){
    dd->betaPostMean[I(l, id)]/= iterations;
    dd->xiPostMean[I(l, id)]/= iterations;
  }
  for(n = 0; n < dd->N; ++n)
    dd->epsilonPostMean[I(n, id)]/= iterations;
}

__global__ void estimates_scale_kernel4(chain_t *dd, double iterations){
  int id = IDX, l, n;
  if(id >= dd->G) return;

  dd->gammaPostMeanSquare[id]/= iterations;
  for(l = 0; l < dd->L; ++l){
    dd->betaPostMeanSquare[I(l, id)]/= iterations;
    dd->xiPostMeanSquare[I(l, id)]/= iterations;
  }
  for(n = 0; n < dd->N; ++n)
    dd->epsilonPostMeanSquare[I(n, id)]/= iterations;
}

__global__ void estimates_scale_kernel5(chain_t *dd, double iterations){
  int g = IDX, p;
  if(g >= dd->G) return;
  for(p = 0; p < dd->P; ++p)
    dd->probs[I(p, g)] /= iterations;
}

void estimates_scale(SEXP hh, chain_t *dd){
  double M = (double) (li(hh, "iterations")[0] * li(hh, "thin")[0]);
  estimates_scale_kernel1<<<1, 1>>>(dd, M);
  estimates_scale_kernel2<<<1, 1>>>(dd, M);
  estimates_scale_kernel3<<<GRID, BLOCK>>>(dd, M);
  estimates_scale_kernel4<<<GRID, BLOCK>>>(dd, M);
  estimates_scale_kernel5<<<GRID, BLOCK>>>(dd, M);
}

#endif // UTIL_ESTIMATES_SCALE_H