#ifndef ALLOC_HD_H
#define ALLOC_HD_H

chain_t *alloc_hd(SEXP hh){
  int N = li(hh, "N")[0],
      L = li(hh, "L")[0],
      G = li(hh, "G")[0];

  chain_t *hd = (chain_t *) calloc(1, sizeof(chain_t));

  CUDA_CALL(cudaMalloc((void**) &(hd->counts), N * G * sizeof(int)));
  CUDA_CALL(cudaMalloc((void**) &(hd->countSums_g), G * sizeof(int)));
  CUDA_CALL(cudaMalloc((void**) &(hd->countSums_n), N * sizeof(int)));
  CUDA_CALL(cudaMalloc((void**) &(hd->design), L * N * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->designUnique), L * N * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->designUniqueN), L * sizeof(int)));
  CUDA_CALL(cudaMalloc((void**) &(hd->seeds), N * G * sizeof(int)));

  CUDA_CALL(cudaMalloc((void**) &(hd->a), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->b), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->c), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->d), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->k), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->p), L * sizeof(int)));
  CUDA_CALL(cudaMalloc((void**) &(hd->r), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->s), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->w), sizeof(double)));

  CUDA_CALL(cudaMalloc((void**) &(hd->beta), L * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->delta), L * G * sizeof(int)));
  CUDA_CALL(cudaMalloc((void**) &(hd->epsilon), N * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->gamma), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->nu), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->omegaSquared), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->pi), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->rho), N * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sigmaSquared), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->tau), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->theta), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->xi), L * G * sizeof(double)));

  CUDA_CALL(cudaMalloc((void**) &(hd->betaPostMean), L * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->deltaPostMean), L * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->epsilonPostMean), N * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->gammaPostMean), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->nuPostMean), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->omegaSquaredPostMean), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->piPostMean), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->rhoPostMean), N * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sigmaSquaredPostMean), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->tauPostMean), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->thetaPostMean), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->xiPostMean), L * G * sizeof(double)));

  CUDA_CALL(cudaMalloc((void**) &(hd->betaPostMeanSquare), L * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->deltaPostMeanSquare), L * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->epsilonPostMeanSquare), N * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->gammaPostMeanSquare), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->nuPostMeanSquare), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->omegaSquaredPostMeanSquare), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->piPostMeanSquare), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->rhoPostMeanSquare), N * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sigmaSquaredPostMeanSquare), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->tauPostMeanSquare), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->thetaPostMeanSquare), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->xiPostMeanSquare), L * G * sizeof(double)));

  CUDA_CALL(cudaMalloc((void**) &(hd->states), N * G * sizeof(curandState_t)));
  CUDA_CALL(cudaMalloc((void**) &(hd->aux), N * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->D), N * G * sizeof(double)));

  return hd;
}

#endif // ALLOC_HD_H
