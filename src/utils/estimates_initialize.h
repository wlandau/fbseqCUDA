#ifndef ESTIMATES_INITIALIZE_H
#define ESTIMATES_INITIALIZE_H

__global__ void estimates_initialize_kernel1(chain_t *dd){
  int l;

  dd->nuPostMean[0] = 0.0;
  dd->tauPostMean[0] = 0.0;

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredPostMean[l] = 0.0;
    dd->thetaPostMean[l] = 0.0;
  }
}

__global__ void estimates_initialize_kernel2(chain_t *dd){
  int l;

  dd->nuPostMeanSquare[0] = 0.0;
  dd->tauPostMeanSquare[0] = 0.0;

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredPostMeanSquare[l] = 0.0;
    dd->thetaPostMeanSquare[l] = 0.0;
  }
}

__global__ void estimates_initialize_kernel3(chain_t *dd){
  int l;

  dd->nuSumDiff[0] = 0.0;
  dd->tauSumDiff[0] = 0.0;

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredSumDiff[l] = 0.0;
    dd->thetaSumDiff[l] = 0.0;
  }
}

__global__ void estimates_initialize_kernel4(chain_t *dd){
  int l;

  dd->nuWidth[0] = INIT_WIDTH;
  dd->tauWidth[0] = INIT_WIDTH;

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredWidth[l] = INIT_WIDTH;
    dd->thetaWidth[l] = INIT_WIDTH;
  }
}

__global__ void estimates_initialize_kernel5(chain_t *dd){
  int id = IDX, l, n;
  if(id >= dd->G) return;

  dd->gammaPostMean[id] = 0.0;
  for(l = 0; l < dd->L; ++l){
    dd->betaPostMean[I(l, id)] = 0.0;
    dd->xiPostMean[I(l, id)] = 0.0;
  }
  for(n = 0; n < dd->N; ++n)
    dd->epsilonPostMean[I(n, id)] = 0.0;
}

__global__ void estimates_initialize_kernel6(chain_t *dd){
  int id = IDX, l, n;
  if(id >= dd->G) return;

  dd->gammaPostMeanSquare[id] = 0.0;
  for(l = 0; l < dd->L; ++l){
    dd->betaPostMeanSquare[I(l, id)] = 0.0;
    dd->xiPostMeanSquare[I(l, id)] = 0.0;
  }
  for(n = 0; n < dd->N; ++n)
    dd->epsilonPostMeanSquare[I(n, id)] = 0.0;
}

__global__ void estimates_initialize_kernel7(chain_t *dd){
  int id = IDX, l, n;
  if(id >= dd->G) return;

  dd->gammaSumDiff[id] = 0.0;
  for(l = 0; l < dd->L; ++l){
    dd->betaSumDiff[I(l, id)] = 0.0;
    dd->xiSumDiff[I(l, id)] = 0.0;
  }
  for(n = 0; n < dd->N; ++n)
    dd->epsilonSumDiff[I(n, id)] = 0.0;
}

__global__ void estimates_initialize_kernel8(chain_t *dd){
  int id = IDX, l, n;
  if(id >= dd->G) return;

  dd->gammaWidth[id] = INIT_WIDTH;
  for(l = 0; l < dd->L; ++l){
    dd->betaWidth[I(l, id)] = INIT_WIDTH;
    dd->xiWidth[I(l, id)] = INIT_WIDTH;
  }
  for(n = 0; n < dd->N; ++n)
    dd->epsilonWidth[I(n, id)] = INIT_WIDTH;
}

__global__ void estimates_initialize_kernel9(chain_t *dd){
  int g = IDX, p;
  if(g >= dd->G) return;
  for(p = 0; p < dd->P; ++p)
    dd->probs[I(p, g)] = 0.0;
}

void estimates_initialize(SEXP hh,chain_t *dd){
  estimates_initialize_kernel1<<<1, 1>>>(dd);
  estimates_initialize_kernel2<<<1, 1>>>(dd);
  estimates_initialize_kernel3<<<1, 1>>>(dd);
  estimates_initialize_kernel4<<<1, 1>>>(dd);
  estimates_initialize_kernel5<<<GRID, BLOCK>>>(dd);
  estimates_initialize_kernel6<<<GRID, BLOCK>>>(dd);
  estimates_initialize_kernel7<<<GRID, BLOCK>>>(dd);
  estimates_initialize_kernel8<<<GRID, BLOCK>>>(dd);
  estimates_initialize_kernel9<<<GRID, BLOCK>>>(dd);
}

#endif // ESTIMATES_INITIALIZE_H
