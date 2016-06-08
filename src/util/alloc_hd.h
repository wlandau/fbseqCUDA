#ifndef UTIL_ALLOC_HD_H
#define UTIL_ALLOC_HD_H

chain_t *alloc_hd(SEXP hh){
  int C = li(hh, "C")[0],
      G = li(hh, "G")[0],
      L = li(hh, "L")[0],
      N = li(hh, "N")[0],
      P = li(hh, "P")[0];

  chain_t *hd = (chain_t *) calloc(1, sizeof(chain_t));

  CUDA_CALL(cudaMalloc((void**) &(hd->bounds), C * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->contrasts), C * L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->counts), N * G * sizeof(int)));
  CUDA_CALL(cudaMalloc((void**) &(hd->design), L * N * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->propositions), P * C * sizeof(int)));

  CUDA_CALL(cudaMalloc((void**) &(hd->countSums_g), G * sizeof(int)));
  CUDA_CALL(cudaMalloc((void**) &(hd->countSums_n), N * sizeof(int)));
  CUDA_CALL(cudaMalloc((void**) &(hd->designUnique), L * N * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->designUniqueN), L * sizeof(int)));
  CUDA_CALL(cudaMalloc((void**) &(hd->probs), P * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->contrastsPostMean), C * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->contrastsPostMeanSquare), C * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->seeds), N * G * sizeof(int)));

  CUDA_CALL(cudaMalloc((void**) &(hd->a), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->b), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->c), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->d), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->h), N * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->k), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->q), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->r), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->s), L * sizeof(double)));

  CUDA_CALL(cudaMalloc((void**) &(hd->beta), L * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->epsilon), N * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->gamma), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->nu), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sigmaSquared), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->tau), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->theta), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->xi), L * G * sizeof(double)));

  CUDA_CALL(cudaMalloc((void**) &(hd->betaStart), L * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->epsilonStart), N * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->gammaStart), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->nuStart), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sigmaSquaredStart), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->tauStart), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->thetaStart), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->xiStart), L * G * sizeof(double)));

  CUDA_CALL(cudaMalloc((void**) &(hd->loglikPostMean), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->betaPostMean), L * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->epsilonPostMean), N * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->gammaPostMean), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->nuPostMean), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sigmaSquaredPostMean), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->tauPostMean), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->thetaPostMean), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->xiPostMean), L * G * sizeof(double)));

  CUDA_CALL(cudaMalloc((void**) &(hd->betaPostMeanSquare), L * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->epsilonPostMeanSquare), N * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->gammaPostMeanSquare), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->nuPostMeanSquare), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sigmaSquaredPostMeanSquare), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->tauPostMeanSquare), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->thetaPostMeanSquare), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->xiPostMeanSquare), L * G * sizeof(double)));

  CUDA_CALL(cudaMalloc((void**) &(hd->betaTune), L * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->epsilonTune), N * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->gammaTune), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->nuTune), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sigmaSquaredTune), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->tauTune), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->thetaTune), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->xiTune), L * G * sizeof(double)));

  CUDA_CALL(cudaMalloc((void**) &(hd->betaTuneAux), L * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->epsilonTuneAux), N * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->gammaTuneAux), G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->nuTuneAux), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->sigmaSquaredTuneAux), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->tauTuneAux), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->thetaTuneAux), L * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->xiTuneAux), L * G * sizeof(double)));

  CUDA_CALL(cudaMalloc((void**) &(hd->aux), N * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->D), N * G * sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->loglik), sizeof(double)));
  CUDA_CALL(cudaMalloc((void**) &(hd->states), N * G * sizeof(curandState_t)));

  return hd;
}

#endif // UTIL_ALLOC_HD_H
